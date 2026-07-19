# Hloubková analýza meta-gl

Datum analýzy: 18. července 2026  
Stav dokumentu: živý podklad k revizi a rozhodnutí; schválené a dokončené
položky jsou výslovně označeny.

## Shrnutí

`meta-gl` má pevný základ: přehledné typované API, slušnou dokumentaci,
funkční CMake balíček, reálný EGL smoke test a dobré pokrytí kompilátory.
Všechny identifikované nálezy 1–7 (včetně ABI a Release kontraktu) byly
přijaty a implementovány ve verzi 0.3.0.

Aktualizované `NEXT.md` už tyto release brány výslovně uvádí a `plan.md`
rozkládá veškerou zbývající práci na samostatné úkoly R01–R75. Nález 6 (Release
contract) byl úspěšně implementován a ověřen (R08–R11), stejně jako nález 5
týkající se ABI (R04–R06).

## Rozsah a provedené ověření

Lokálně prošlo:

- GCC Debug static: 5/5 testů;
- GCC Release shared: 5/5 testů;
- GCC ASan/UBSan s nastavením používaným v CI: 5/5 testů;
- Clang Debug: 4/4 testů;
- reálný EGL/GPU smoke test;
- sestavení příkladů a dokumentace Doxygen;
- verifikátor API: 358 wrapperů, 360 loader symbolů a přesné povinné sady
  142/104/68/44 funkcí GLES 2.0/3.0/3.1/3.2;
- `clang-tidy` bez závažné analyzer chyby; hlášení se týkala především
  nevhodných návrhů na zmenšení OpenGL enumů.

Zelený testovací výsledek je důležitý, ale současné testy nepokrývají některé
níže popsané sémantické, ABI a lifecycle scénáře.

## Nálezy doporučené k vyřešení před 0.3.0

<a id="finding-1"></a>
### 1. ✅ Opraveno: `glClearBufferfi` nešlo typově zavolat správně

**Rozhodnutí 18. července 2026:** přijato pro 0.3.0 a implementováno.
`glClearBufferfi` nyní přijímá jen `depth` a `stencil` a pevné GL argumenty
doplňuje interně. Společný `ClearBuffer` byl zároveň rozdělen na přesné
domény pro float, signed integer a unsigned integer clear funkce. Následující
text zachovává původní nález a jeho odůvodnění.

**Integrační omezení:** současný `easy-gl` používá odstraněný `ClearBuffer` i
původní čtyřparametrové `glClearBufferfi`. L1 proto nesmí být sloučeno do
sdíleného `develop`, dokud nebude schválena kompatibilní vrstva nebo
koordinovaná migrace `easy-gl` v samostatném worktree.

Wrapper při auditu přijímal `ClearBuffer`, jehož hodnoty byly jen `Color`,
`Depth` a `Stencil`. Aktuální bezpečná deklarace je v
[Functions.hpp](include/metagl/Functions.hpp#L391) a nové přesné domény jsou
v [Enums.hpp](include/metagl/Enums.hpp#L1768).

Pro `glClearBufferfi` je jedinou platnou hodnotou `GL_DEPTH_STENCIL` a
`drawbuffer` musí být nula. Správný token v enumu není.

Zvažovaná řešení:

- zavést úzký enum obsahující pouze `DepthStencil`; nebo
- přidat overload bez parametrů `buffer` a `drawbuffer`, který obě pevné
  hodnoty doplní interně.

<a id="finding-2"></a>
### 2. ✅ Opraveno: `glCopyImageSubData` neumělo reprezentovat renderbuffery

**Rozhodnutí 18. července 2026:** přijato pro 0.3.0 a implementováno
aditivně. Přesný `ImageCopyTextureTarget` nyní vylučuje texture buffer a
jednotlivé cube-map faces. Čtyři typované overloady pokrývají všechny
kombinace `TextureId` a `RenderbufferId`; u renderbufferů doplňují pevné
target, level, z a depth hodnoty interně. Původní `GLuint + TextureTarget`
overload zůstává zachovaný kvůli kompatibilitě existujícího `easy-gl`.
Následující text zachovává původní nález a jeho odůvodnění.

Při auditu parametr cíle používal `TextureTarget`, který
`GL_RENDERBUFFER` nereprezentoval. Aktuální overloady jsou v
[Functions.hpp](include/metagl/Functions.hpp#L693) a přesná texture target
doména v [Enums.hpp](include/metagl/Enums.hpp#L806).

Zvažovaná řešení:

- zavést `ImageCopyTarget` s přesně povolenými texture targety a
  `Renderbuffer`;
- přidat overloady rozlišující `TextureId` a `RenderbufferId`, aby běžný
  uživatel nemusel pracovat se syrovým `GLuint`.

Nálezy 1 a 2 vycházejí přímo z povolených domén OpenGL ES 3.2, nikoliv jen
z preference stylu API. Referenčním podkladem je
[Khronos OpenGL ES 3.2 specification](https://registry.khronos.org/OpenGL/specs/es/3.2/es_spec_3.2.pdf).

<a id="finding-3"></a>
### 3. ✅ Opraveno: po ztrátě kontextu zůstával viditelný stav loaderu

**Rozhodnutí 18. července 2026:** přijato pro 0.3.0 a implementováno.
Context loss nyní zachová generation a stav `Lost`, ale vyčistí aktuální
API/version metadata a capabilities. Mapa dostupnosti se skryje a vyčistí,
`IsFunctionAvailable()` i `AllFunctionsLoaded()` vracejí `false` a všech 358
wrapperů v Debug režimu vyžaduje také inicializovaný kontext. Úspěšný reload
publikuje loader state a capabilities znovu před restore listenery.
Následující text zachovává původní nález a jeho odůvodnění.

Při auditu `InvalidateFunctionsAfterContextLoss()` pouze nastavovalo
`initialized = false`. Neukrývalo mapu dostupnosti funkcí ani detekované
capabilities.

`IsFunctionAvailable()` nekontroluje inicializaci
([Functions.cpp](src/Functions.cpp#L1388)), `AllFunctionsLoaded()` také ne
([Functions.cpp](src/Functions.cpp#L1395)) a wrappery kontrolují pouze
nenulový ukazatel ([Functions.cpp](src/Functions.cpp#L1401)).

Po `MarkContextLost()` proto mohla knihovna hlásit dostupné funkce a v Debug
sestavení dovolit volání přes staré adresy. To bylo v rozporu s vlastním
architektonickým invariantem projektu
([NEXT.md](NEXT.md#8-architectural-invariants)).

Možná řešení:

- podmínit dostupnost funkcí a capabilities aktivní inicializací;
- po ztrátě kontextu atomicky skrýt nebo resetovat publikovaný stav;
- v Debug režimu ověřovat před wrapper voláním také platný kontext;
- rozhodnout, zda capabilities představují aktuální stav, nebo historický
  snapshot, a podle toho je pojmenovat a dokumentovat.

<a id="finding-4"></a>
### 4. ✅ Opraveno: inicializace validovala jen minimum GLES 2

Původně `Initialize()` ověřovalo pouze společné minimum GLES 2, ale následná
detekce capabilities mohla podle textu oznámit ES 3.x a zavolat chybějící
`glGetStringi`.

Nyní se nejdříve načtou pouze `glGetString`, `glGetIntegerv` a `glGetError`.
Neplatný, prázdný nebo nepodporovaný `GL_VERSION` se odmítne. Zbytek funkcí se
načítá do kandidátní tabulky a validuje proti přesné kumulativní sadě pro
GLES 2.0, 3.0, 3.1 nebo 3.2. Desktop se přijímá od OpenGL 3.3 a vyžaduje
společné minimum plus `glGetStringi`. WebGL zůstává samostatnou
browser-kompatibilní podmnožinou: WebGL 1 vyžaduje minimum ES 2.0 a WebGL 2
navíc `glGetStringi`; nepožaduje funkce ES 3, které WebGL 2 neposkytuje.
Teprve úspěšný kandidát se publikuje
([Functions.cpp](src/Functions.cpp), [RequiredFunctions.inc](src/RequiredFunctions.inc)).

Verifikátor porovnává s Khronos `gl32.h` všech 142/104/68/44 funkcí
jednotlivých verzí. Mock testy pokrývají nulový a poškozený `GL_VERSION`,
desktop GL 2.1, chybějící `glGetStringi` a přesné hranice povinnosti funkcí
mezi ES 2.0, 3.0, 3.1 a 3.2
([test_mock_loader.cpp](tests/test_mock_loader.cpp)).

<a id="finding-5"></a>
### 5. ✅ Opraveno: SONAME nezachycuje nekompatibilitu minor verzí 0.x

**Rozhodnutí 18. července 2026:** přijato pro 0.3.0 a implementováno.
Bylo rozhodnuto ponechat `SOVERSION 0` jako signál chybějící stability ABI
před verzí 1.0. Pro včasnou detekci nechtěných změn a zajištění souladu s
plánem byl implementován automatizovaný test `metagl-soname-test`, který
při každém shared-build testu ověřuje, že výsledné SONAME je skutečně
`libmeta-gl.so.0`.

<a id="finding-6"></a>
### 6. ✅ Opraveno: „Checked“ konverze byly v Release nekontrolované

**Rozhodnutí 18. července 2026:** přijato pro 0.3.0 a implementováno.
Pomocné funkce pro kontrolu velikostí a matic nyní v Release sestavení místo
pouhého asertu volají `std::terminate()`. Deklarace `noexcept` byly odstraněny
tam, kde to bylo s ohledem na sémantiku ukončení programu zavádějící, a kontrakt
byl zdokumentován v hlavním headeru. Negativní testy ověřují vynucené ukončení
při přetečení nebo neplatných vstupech.

<a id="finding-7"></a>
### 7. ✅ Opraveno: Test nainstalovaného balíčku neovlivňoval skutečné linkování

**Rozhodnutí 18. července 2026:** přijato pro 0.3.0 a implementováno.
Testovací aplikace `package-consumer` nyní volá skutečné out-of-line symboly
(`GetContextStatus`, `GetContextGeneration`), které vynucují linkování proti
knihovně i v shared variantě. CTest navíc ověřuje jak statické, tak sdílené
linkování na Linuxu, včetně spuštění výsledného binárního souboru.

## Další nedostatky domén veřejného API

<a id="finding-8"></a>
### 8. `glMemoryBarrierByRegion` přijímá příliš širokou masku

`glMemoryBarrierByRegion` používá stejný `MemoryBarrierMask` jako obecný
`glMemoryBarrier` ([Functions.hpp](include/metagl/Functions.hpp#L885)).
OpenGL ES 3.2 zde ale dovoluje jen šest konkrétních bitů a `ALL`.

Řešením může být samostatný `MemoryBarrierByRegionMask` nebo bezpečný
konverzní helper z jeho užší domény.

<a id="finding-9"></a>
### 9. `DebugObjectLabel` neobsahuje všechny platné identifikátory

Enum postrádá přinejmenším framebuffer, renderbuffer, texture a transform
feedback, které specifikace pro `ObjectLabel` povoluje.

Je potřeba enum doplnit a přidat reprezentativní runtime nebo compile-time
test všech podporovaných object domains.

<a id="finding-10"></a>
### 10. Invalidace výchozího framebufferu není plně reprezentovatelná

`glInvalidateFramebuffer` používá `FramebufferAttachment`, který neumí
tokeny `GL_COLOR`, `GL_DEPTH` a `GL_STENCIL` určené pro výchozí framebuffer.

Je vhodné rozhodnout mezi samostatnou doménou pro default framebuffer,
explicitními overloady nebo širším typem s jasnou validací vazby na target.

<a id="finding-11"></a>
### 11. Texture parameter setter přijímá query-only tokeny

`glTexParameter*` přijímá široký `TextureParameter`
([Functions.hpp](include/metagl/Functions.hpp#L683)), který obsahuje také
hodnoty určené pouze pro dotazy, například immutable format, samples nebo
buffer offset.

Setter a getter domény by měly být oddělené nebo by měl být přidán přesný
typed overload pro zapisovatelné parametry.

<a id="finding-12"></a>
### 12. Immutable texture storage neumí komprimované interní formáty

`glTexStorage2D/3D` přijímá jen `InternalFormat`
([Functions.hpp](include/metagl/Functions.hpp#L654)), zatímco podporované
komprimované interní formáty mají vlastní oddělený enum.

Je třeba zvážit společnou přesnou doménu immutable storage formátů nebo
overloady pro oba stávající enumy.

<a id="finding-13"></a>
### 13. Transform feedback primitive domain je příliš široká

`glBeginTransformFeedback` přijímá obecný `PrimitiveType`, a tedy i režimy,
které funkce nepovoluje. Měl by existovat úzký enum omezený na `Points`,
`Lines` a `Triangles`.

U nálezů 8–13 lze zachovat kompatibilitu přidáním přesných overloadů a
označením starých širokých overloadů jako deprecated. Vlastní invariant
projektu už požaduje, aby enumové domény modelovaly legální GL parametry
([NEXT.md](NEXT.md#8-architectural-invariants)).

## Platforma, ABI a lifecycle

<a id="finding-14"></a>
### 14. Kontrakt loader callbacku není dostatečně přenositelný

Loader callback je definován jako funkce vracející `void*`. EGL, GLFW a WGL
však používají vlastní typy funkčních ukazatelů, takže uživatel potřebuje
adaptér a potenciálně neportabilní konverzi.

Zvlášť přímé použití WGL je potřeba dokumentovat přesněji:
`wglGetProcAddress` vyžaduje aktuální kontext, vrací rozšiřující funkce a
adresy mohou záviset na pixel formátu nebo kontextu. Pro core Windows symboly
je obvykle potřeba fallback do `opengl32.dll`; viz
[Microsoft wglGetProcAddress documentation](https://learn.microsoft.com/nl-nl/windows/win32/api/wingdi/nf-wingdi-wglgetprocaddress).

Možná řešení zahrnují formální adapter contract, dodávané platformní adaptéry
a dokumentovaný WGL fallback včetně odmítnutí sentinel hodnot.

<a id="finding-15"></a>
### 15. Exportované ABI je širší než veřejné API

Projekt používá `WINDOWS_EXPORT_ALL_SYMBOLS`
([CMakeLists.txt](CMakeLists.txt#L40)) a nemá centrální export macro ani
výchozí hidden visibility. Veřejně tak mohou být dostupné interní globální
proměnné, detail funkce a implementační STL symboly.

Doporučeným směrem je `METAGL_API`, hidden visibility ve výchozím stavu a
explicitní export pouze dokumentovaného veřejného ABI.

<a id="finding-16"></a>
### 16. Thread a multi-context model potřebuje explicitní rozhodnutí

Loader table, capabilities, listenery a debug buffer jsou globální.
Knihovna je proto prakticky navržena pro jeden aktivní kontext a
koordinovanou inicializaci, ale tento rozsah není všude vyjádřen jako
jednoznačný kontrakt.

Je potřeba rozhodnout, zda je single-context model záměrná hranice knihovny,
nebo zda se mají loader/context data přesunout do explicitního či
thread-local state objektu.

<a id="finding-17"></a>
### 17. Snapshot listenerů neřeší zničení jiného listeneru

Snapshot seznamu chrání self-removal během dispatch, ale listener A může
odebrat a zničit listener B, jehož syrový ukazatel stále čeká ve snapshotu.

Možná řešení:

- před každým callbackem znovu ověřit registraci;
- použít RAII connection token;
- definovat vlastnictví přes bezpečnější handle nebo lifetime contract.

Současně je vhodné rozhodnout, jaký stav má být publikován, pokud některý
restore listener vyhodí výjimku po částečné obnově zdrojů.

<a id="finding-18"></a>
### 18. Debug kontrola přes `glGetError` mění aplikační error state

Automatické volání `glGetError` spotřebovává chyby, které by jinak mohl číst
uživatel knihovny, a aktuální kontrola zachytí jen jednu chybu po wrapper
volání.

Toto chování by mělo být explicitně dokumentované a volitelné. Pokud zůstane,
je vhodné zvážit callback/reporting policy a omezené vyprázdnění celé error
fronty.

## Udržovatelnost a testovací strategie

<a id="finding-19"></a>
### 19. Mechanická část API je ručně udržovaná

Největší dlouhodobé riziko představují velké ručně synchronizované soubory:

- `src/Functions.cpp`: přibližně 4 300 řádků;
- `include/metagl/Functions.hpp`: přibližně 1 800 řádků;
- `Enums.hpp` a `EnumNames.hpp`: dohromady přes 3 600 řádků.

Současný verifikátor hlídá jména a základní shodu, ale neověřuje přesné
signatury, verze, legální enumové domény ani úplnost povinných funkcí.

Dlouhodobým řešením může být generování mechanických částí z Khronos
`gl.xml` a malý ručně spravovaný policy soubor určující silné typy, verze,
domény a kompatibilní overloady.

<a id="finding-20"></a>
### 20. Chybí runtime pokrytí důležitých platforem a lifecycle scénářů

Současný real-GPU test pokrývá Linux EGL/Mesa. Automatizovaný reálný browser
test context loss/restore a nativní WGL, ANGLE, GLX či vendor driver scénáře
nejsou pokryté.

Prioritním doplněním je browser test s `WEBGL_lose_context`; následovat může
Windows WGL nebo ANGLE runtime test a kontrola alespoň jednoho desktop GL
loader fallback scénáře.

## Navržené pořadí rozhodování

<a id="finding-21"></a>
### 21. Release disposition

Před rozhodnutím o vydání 0.3.0 doporučuji dokončit revizi nálezů 5–7;
nálezy 1–4 jsou již implementovány. Nálezy 5–7 ovlivňují ABI a
důvěryhodnost release ověření.

Navržené skupiny pro revizi:

1. **Před 0.3.0:** zbývající nálezy 5–7 a rozhodnutí o vydání.
2. **Kandidáti pro 0.4:** nálezy 8–18.
3. **Dlouhodobý směr k 1.0:** nálezy 19–20.

Celkově je základ projektu kvalitní a většina nálezů je řešitelná bez
přepisování celé architektury. Klíčové je sladit skutečné chování s tím, co
typové API, dokumentace a release metadata uživatelům slibují.

## Doplňkový nález (2026-07-19)

<a id="finding-22"></a>
### 22. ✅ Rozhodnuto: ekvivalence OpenGL ES tierů na desktopu (z `opengl.md`)

Samostatná analytická poznámka `opengl.md` (2026-07-19) zkoumala, zda a jak
by `meta-gl` mohl na desktopovém OpenGL 3.3+ reportovat ekvivalentní
OpenGL ES tier (ES 3.0/3.1/3.2), aniž by rozšířil veřejný API surface o
desktop-only funkce/enumy. Popsala pět nálezů a šest navrhovaných změn.

**Rozhodnutí 19. července 2026:**

- **Přijato:** rozšířit `RequiredApiLevel` o desktop tiery analogické ES
  (`Desktop33` zůstává ES-2.0-ekvivalentní baseline; přidávají se tiery
  odpovídající ES 3.0/3.1/3.2) a validovat proti nim
  `gles30/31/32_required_names` — výhradně jako interní krok při
  `Initialize()`, beze změny veřejného API (viz R76).
- **Přijato:** namísto kontroly ARB fallbacku pro jednotlivé funkce
  detekovat `GL_ARB_ES3_1_compatibility` / `GL_ARB_ES3_2_compatibility`
  jako jediný rychlý signál, že desktop driver danou úroveň poskytuje i na
  nižší základní verzi (viz R77).
- **Přijato:** doplnit mock testy pro hraniční desktop verze (3.3, 4.1,
  4.3) s/bez těchto extensions, aby byly hranice mezi tiery pokryty testy
  (viz R78).
- **Zamítnuto jako mimo rozsah:** veřejné zpřístupnění tierů přes
  `SupportsGLES30/31/32()` nebo nové paralelní pole typu
  `desktopGles30Equivalent` v `Capabilities` — desktop a ES flagy zůstávají
  záměrně oddělené, tiery z tohoto nálezu slouží jen interní validaci.
- **Zamítnuto jako mimo rozsah:** per-funkce ARB fallback matice
  (`ARB_texture_storage`, `ARB_get_program_binary`,
  `ARB_invalidate_subdata`, `ARB_internalformat_query`) — nahrazeno jediným
  signálem `GL_ARB_ES3_x_compatibility` výše.
- **Zamítnuto jako mimo rozsah:** dotaz na `GL_CONTEXT_PROFILE_MASK` — nemá
  funkční dopad, protože `meta-gl` nikdy neexponuje fixed-function API.
- **Potvrzeno jako trvalé pravidlo:** žádné nové wrappery pro čistě
  desktop-only funkce/enumy; API surface zůstává výhradně podmnožinou
  OpenGL ES 3.2.

Analytická poznámka `opengl.md` byla po tomto rozhodnutí smazána; závěry
jsou zaznamenány zde a jako úkoly R76–R78 v [`plan.md`](plan.md).
