"""R47 - Unix exported-symbol allowlist/policy test.

See plan.md R44-R47. Rather than pinning an
exact list of all ~394 mangled wrapper symbols (which would need editing on
every new GL function wrapper and would conflict with the project's
thin-wrapper/minimal-maintenance philosophy, see CLAUDE.md), this test
enforces the R44 export policy directly against the shared library's
dynamic symbol table:

  1. Every defined dynamic symbol must be a function/text symbol (nm type
     "T"); no exported data/object symbols are expected.
  2. Every defined dynamic symbol's demangled name must live in the
     ``metagl::`` namespace; nothing from an internal anonymous namespace,
     the C++ runtime, or a leaked implementation detail is exported.
  3. Any symbol under ``metagl::detail::`` must be explicitly allowlisted
     below; today only the documented internal-only diagnostic
     ``metagl::detail::GetDesktopEsTier()`` (see DesktopEsTier.hpp) is
     exported on purpose.
  4. A small set of landmark public entry points must be present, to catch
     a regression that accidentally hides the whole public surface (e.g. a
     broken METAGL_API/visibility change) rather than just one symbol.
"""

import subprocess
import sys

ALLOWED_DETAIL_SYMBOLS = {
    "metagl::detail::GetDesktopEsTier()",
}

REQUIRED_LANDMARK_SYMBOLS = (
    "metagl::Initialize(",
    "metagl::IsInitialized()",
    "metagl::AllFunctionsLoaded()",
    "metagl::IsFunctionAvailable(",
    "metagl::GetContextStatus()",
    "metagl::glEnable(",
    "metagl::glGetError()",
)


def read_defined_dynamic_symbols(lib_path):
    output = subprocess.check_output(
        ["nm", "-D", "--defined-only", "-C", lib_path],
        stderr=subprocess.STDOUT,
    ).decode()

    symbols = []
    for line in output.splitlines():
        parts = line.split(None, 2)
        if len(parts) != 3:
            continue
        _address, sym_type, name = parts
        symbols.append((sym_type, name))
    return symbols


def check(lib_path):
    symbols = read_defined_dynamic_symbols(lib_path)
    if not symbols:
        print(f"No defined dynamic symbols found in {lib_path}; "
              "nm failed or the library is empty.")
        return False

    errors = []
    names = {name for _sym_type, name in symbols}

    for sym_type, name in symbols:
        if sym_type != "T":
            errors.append(
                f"unexpected non-function exported symbol ({sym_type}): {name}")
            continue
        if not name.startswith("metagl::"):
            errors.append(
                f"leaked symbol outside the metagl:: namespace: {name}")
            continue
        if "::detail::" in name and name not in ALLOWED_DETAIL_SYMBOLS:
            errors.append(
                "leaked internal metagl::detail:: symbol not on the "
                f"allowlist: {name}")

    for landmark in REQUIRED_LANDMARK_SYMBOLS:
        if not any(name.startswith(landmark) for name in names):
            errors.append(
                f"missing expected public symbol starting with: {landmark}")

    if errors:
        print(f"Exported-symbol policy violations in {lib_path}:")
        for error in errors:
            print(f"  - {error}")
        return False

    print(
        f"OK: {len(symbols)} exported symbols in {lib_path} satisfy the "
        "R44-R47 policy (metagl:: namespace, function-only, detail:: "
        "allowlist, landmark symbols present).")
    return True


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: test_export_symbols.py <library_path>")
        sys.exit(1)

    if check(sys.argv[1]):
        sys.exit(0)
    else:
        sys.exit(1)
