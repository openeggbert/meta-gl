#!/usr/bin/env python3
"""Verify that the generated-style GL wrapper surface remains synchronized."""

from __future__ import annotations

import re
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src/Functions.cpp").read_text(encoding="utf-8")
HEADER = (ROOT / "include/metagl/Functions.hpp").read_text(encoding="utf-8")
GL32 = (ROOT / "third_party/Khronos/GLES3/gl32.h").read_text(encoding="utf-8")

errors: list[str] = []


def fail(message: str) -> None:
    errors.append(message)


parts = re.split(r"^    // #(\d+)\n", SOURCE, flags=re.MULTILINE)
wrappers: list[tuple[int, str, str]] = []
for index in range(1, len(parts), 2):
    number = int(parts[index])
    body = parts[index + 1]
    match = re.search(r"\b(gl[A-Z]\w*)\s*\(", body)
    if match is None:
        fail(f"wrapper #{number} has no gl* definition")
        continue
    wrappers.append((number, match.group(1), body))

numbers = [number for number, _, _ in wrappers]
names = [name for _, name, _ in wrappers]
name_set = set(names)

if numbers != list(range(1, 359)):
    fail("wrapper numbering is not the contiguous range 1..358")
if len(name_set) != 358:
    fail(f"expected 358 unique wrapper names, found {len(name_set)}")

for number, name, body in wrappers:
    if "assert(detail::g_gl." not in body:
        fail(f"wrapper #{number} {name} has no function-pointer assertion")
    # glGetError deliberately avoids the generic macro because that macro
    # performs another glGetError call.
    if name != "glGetError" and "METAGL_DEBUG_LOG" not in body:
        fail(f"wrapper #{number} {name} has no debug log hook")

header_names = set(re.findall(r"\b(gl[A-Z]\w*)\s*\(", HEADER))
missing_declarations = sorted(name_set - header_names)
if missing_declarations:
    fail("source wrappers missing from Functions.hpp: "
         + ", ".join(missing_declarations))

loaded_names = set(re.findall(
    r'detail::load<.*?>\(\s*loader,\s*"(gl[A-Za-z0-9_]+)"',
    SOURCE,
    flags=re.DOTALL,
))
missing_loads = sorted(name_set - loaded_names)
if missing_loads:
    fail("source wrappers missing loader entries: " + ", ".join(missing_loads))

allowed_desktop_fallbacks = {"glDepthRange", "glClearDepth"}
unexpected_loads = sorted(loaded_names - name_set - allowed_desktop_fallbacks)
if unexpected_loads:
    fail("unexpected loader-only entries: " + ", ".join(unexpected_loads))

gles2_section_match = re.search(
    r"#ifndef GL_ES_VERSION_2_0(.*?)#endif /\* GL_ES_VERSION_2_0 \*/",
    GL32,
    flags=re.DOTALL,
)
if gles2_section_match is None:
    fail("could not locate the GLES 2.0 prototype section in gl32.h")
    gles2_names: set[str] = set()
else:
    gles2_names = set(re.findall(
        r"GL_APICALL\b.*?\b(gl[A-Za-z0-9_]+)\s*\(",
        gles2_section_match.group(1),
    ))
    if len(gles2_names) != 142:
        fail(f"expected 142 GLES 2.0 prototypes, found {len(gles2_names)}")

minimum_match = re.search(
    r"static bool minimum_loaded\(.*?\n    \}(.*?)"
    r"static bool all_loaded",
    SOURCE,
    flags=re.DOTALL,
)
if minimum_match is None:
    fail("could not locate minimum_loaded()")
else:
    minimum_fields = set(re.findall(
        r"\bgl\.([A-Za-z0-9_]+)", minimum_match.group(0)))
    missing_core = sorted(
        name for name in gles2_names if name.removeprefix("gl") not in minimum_fields
    )
    if missing_core:
        fail("GLES 2.0 functions absent from minimum_loaded(): "
             + ", ".join(missing_core))

if errors:
    for error in errors:
        print(f"ERROR: {error}", file=sys.stderr)
    raise SystemExit(1)

print(
    "API verification passed: "
    f"{len(wrappers)} wrappers, {len(loaded_names)} loader names, "
    f"{len(gles2_names)} GLES 2.0 minimum functions."
)
