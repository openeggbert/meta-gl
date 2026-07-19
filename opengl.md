# OpenGL ES support in meta-gl and the path to "OpenGL ES-like on desktop OpenGL"

This document is an analysis-only note. It records which OpenGL ES versions
`meta-gl` actually supports today (verified directly in the code, not just in
the docs), what already exists for desktop OpenGL, and what would need to
change so that `meta-gl` can support desktop OpenGL as a first-class target
while still exposing only the OpenGL ES subset of functionality (i.e. no
desktop-only entry points or enums, ever).

## Which OpenGL ES versions meta-gl actually supports today

- **OpenGL ES 2.0–3.2** is fully supported and **enforced** at `Initialize()`:
  - `src/Functions.cpp` (`detect_version()`) parses the version out of the
    `GL_VERSION` string and classifies it into
    `RequiredApiLevel::Gles20/30/31/32`.
  - `minimum_loaded()` verifies the common ES 2.0 minimum (about 142
    functions).
  - `src/RequiredFunctions.inc` contains the exact lists
    `gles30_required_names` (+104), `gles31_required_names` (+68),
    `gles32_required_names` (+44), which are additionally enforced according
    to the detected level (`Functions.cpp`, roughly lines 725–750).
  - `tools/verify_api.py` verifies these lists against the vendored
    `GLES3/gl32.h`.
  - In total, **358 functions** are wrapped (`OpenGL_ES.md`), with no ES 1.x
    fixed-function API.
- **WebGL 1/2** (Emscripten) is supported as a separate, slightly relaxed
  subset (WebGL 2 does not require the full set of ES 3.0 mandatory
  functions, because WebGL itself is already narrower).
- OpenGL ES older than 2.0 is **not**, and will not be, supported
  (fixed-function pipeline).

## What already exists for desktop OpenGL

Desktop support **already exists partially** (task J5 in
`archive/plan20260719.md`, implemented):

- `ApiKind::OpenGL` + `Capabilities::desktop_gl` + `SupportsDesktopOpenGL()`.
- `detect_version()` classifies any version `>= 3.3` as
  `RequiredApiLevel::Desktop33`.
- For desktop, only `minimum_loaded(gl, desktop=true)` **plus**
  `glGetStringi` are validated — roughly an ES-2.0-equivalent core, not the
  higher tiers.
- Adaptation of `glDepthRangef`/`glClearDepthf` → `glDepthRange`/
  `glClearDepth` (desktop uses `double`, not `float`).
- Functions available only on ES (`glShaderBinary`,
  `glReleaseShaderCompiler`, `glGetShaderPrecisionFormat`) are optional on
  desktop (`IsFunctionAvailable()`).
- All 358 wrappers are loaded under the **same GLES names**
  (`glBindVertexArray`, `glDrawRangeElements`, `glTexStorage2D`, …) on both
  desktop and ES — this works because the desktop OpenGL 3.3+ core profile
  shares these names with ES (confirmed by a mock test with `GL 4.6` in
  `test_mock_loader.cpp`).
- No desktop-only functions/enums are added — the API surface remains
  strictly an ES subset. This particular requirement from the task is
  therefore **already satisfied today**.

## Key findings — what is missing for full "ES-like, but on desktop"

1. **Tiered GLES flags do not work on desktop.** `SupportsGLES20/30/31/32()`
   are `true` only for actual `ApiKind::OpenGLES`/`WebGL`
   (`Context.cpp`, lines 97–104). On desktop they are **always `false`**,
   even when the driver actually provides an ES 3.x equivalent (confirmed by
   the "Desktop context does not claim GLES" test). So an application has no
   uniform way to ask "do I have ES-3.1-level functionality available?"
   regardless of whether it runs on ES or desktop — it has to manually parse
   `major`/`minor` or call `IsFunctionAvailable()` for every function
   individually.
2. **Mandatory validation for desktop does not distinguish tiers.** Any
   version `>= 3.3` falls into a single `Desktop33` bucket and only the
   ES-2.0 baseline is checked. `gles30/31/32_required_names` are never
   checked for desktop at all (`Functions.cpp` line 734:
   `if (desktop) return gl.GetStringi != nullptr;` — nothing further is
   checked). `Initialize()` can thus "pass" even on `GL 3.3`, where
   functions corresponding to ES 3.1/3.2 (compute shaders, debug output,
   tessellation/geometry) are missing.
3. **Not every ES-3.x equivalent is already in desktop OpenGL core as of
   version 3.3.** For example `glTexStorage2D/3D` (core only from desktop GL
   4.2 / `ARB_texture_storage`), `glGetProgramBinary`/`glProgramBinary`
   (4.1 / `ARB_get_program_binary`), `glInvalidateFramebuffer`
   (4.3 / `ARB_invalidate_subdata`), `glGetInternalformativ`
   (4.2 / `ARB_internalformat_query`). A real "ES 3.0-equivalent" desktop
   target therefore actually needs more like GL 4.2–4.3, not 3.3 — unless
   the availability of the corresponding ARB extensions on lower versions is
   also taken into account.
4. **Khronos directly addresses this exact scenario with the
   `GL_ARB_ES3_1_compatibility` and `GL_ARB_ES3_2_compatibility`
   extensions** — these are not mentioned or detected anywhere in the code
   or in the analysis, even though they are the most natural signal that
   "this desktop driver provides an ES-3.1/3.2-equivalent subset" even on a
   lower base desktop version.
5. The context profile (`GL_CONTEXT_PROFILE_MASK` — core vs. compatibility)
   is not queried. Because meta-gl never exposes fixed-function API, this is
   not a functional problem, but it is a missing diagnostic signal (a
   compatibility profile can hide differing behavior/extensions).

## Proposed changes (analysis only, no code changes)

Goal: keep the ES function subset strictly as-is (no new desktop-only entry
points/enums), but refine *detection and validation* so that desktop can
report an equivalent ES tier:

1. Extend `RequiredApiLevel` with desktop tiers analogous to ES (e.g.
   `Desktop33` → ES-2.0-equivalent, `Desktop~ES30`, `Desktop~ES31`,
   `Desktop~ES32`) instead of one flat `Desktop33`.
2. For these tiers, run the corresponding `gles3x_required_names` check, but
   with a **fallback to ARB extensions** wherever a function is only in
   desktop core starting from a higher version than the tier's threshold
   (`ARB_texture_storage`, `ARB_invalidate_subdata`,
   `ARB_get_program_binary`, `ARB_internalformat_query`, …).
3. Explicitly detect `GL_ARB_ES3_1_compatibility` / `GL_ARB_ES3_2_compatibility`
   as an additional/fast signal of a higher tier's availability on desktop.
4. Unify the public API: either let `gles30/31/32` report `true` for desktop
   too (in which case the naming would need to be reframed as "ES-3.x-level
   functionality," not literally "this is GLES"), or add a parallel field
   such as `desktopGles30Equivalent` in `Capabilities`, so callers do not
   need to distinguish backends themselves.
5. Keep everything else unchanged: no new wrappers for purely desktop-only
   functions/enums, no expansion of `enum class` domains beyond ES 3.2 —
   only extend the detection/validation layer (`Functions.cpp`,
   `Context.cpp`, `RequiredFunctions.inc`), consistent with the `CLAUDE.md`
   rule of "small, reviewable patches, one domain at a time."
6. Add mock tests for lower desktop versions (3.3, 4.1, 4.3) with/without
   the relevant ARB extensions, to cover the boundaries between tiers
   (analogous to the current `GL 4.6` tests).

This is a purely analytical conclusion — no source code changes were made,
as requested.
