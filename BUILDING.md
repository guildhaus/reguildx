# Building

The game builds with CMake and clang from [llvm-mingw](https://github.com/mstorsjo/llvm-mingw),
targeting 32-bit Windows (`i686-w64-mingw32`). The toolchain is self-contained (headers, CRT, DirectX
import libraries), so no Visual Studio, Windows SDK or DirectX SDK is needed. It also cross-compiles from
Linux or macOS.

## Requirements

- CMake >= 3.25 and Ninja
- llvm-mingw (tested: 20261117, clang 23.1). Any host build works (`ucrt-x86_64` on Windows). The
  `ucrt-i686` build is useful too: its 32-bit `lldb` can debug the game natively, while the x86_64
  `lldb` can't unwind WoW64 processes.

## Build and run

Everything is CMake: building, staging a run directory and starting the game.

```sh
cmake --preset play               # once: configure (the plain preset likewise)
cmake --build --preset run        # build, stage build-cmake/run, run the game in a window
cmake --build --preset run-plain  # the same with the plain preset
cmake --build --preset debug      # under the 32-bit lldb
cmake --build --preset play       # build only -> build-cmake/play/GildeGold.exe
```

| preset  | options                                                                   |
|---------|---------------------------------------------------------------------------|
| `plain` | none: the game as the original builds it (garbled in a window on a 32-bit desktop) |
| `play`  | `GILDEGOLD_FIX_16BPP` (16-bit back buffer in a window), `GILDEGOLD_FRAME_DUMP` |

Cache variables, all with defaults:

| variable | default |
|---|---|
| `LLVM_MINGW_ROOT` | the `LLVM_MINGW_ROOT` environment variable, else the newest `C:/Tools/llvm-mingw-*-x86_64`, else `PATH` |
| `GILDEGOLD_GAME_DIR` | `C:/Program Files/GOG Galaxy/Games/The Guild Gold` (the install, never written) |
| `GILDEGOLD_RUN_DIR` | `build-cmake/run` |
| `GILDEGOLD_RUN_ARGS` | `DIRECTWINDOW` |
| `GILDEGOLD_LLDB` | the newest `C:/Tools/llvm-mingw-*-i686/bin/lldb.exe` (the `debug` target needs a 32-bit lldb) |
| `GILDEGOLD_DEBT_WARNINGS` | `OFF`: hides the ~11k loose-typing warnings (see below) |

Staging (`cmake/stage-run.cmake`, also the `stage` target) links the install's folders into the run
directory and copies its ini / dll / asi files once. The run directory's `game.ini` is its own: the first
run turns the intro off and the volumes to 0, and every run enforces the window mode and the sound
switches. The options menu's settings are kept; delete the file for a fresh copy of the install's. On
current Windows, DirectDraw only reports 16-bit display modes under the `DWM8And16BitMitigation`
compatibility layer, and without it the game exits during start-up. Staging sets it for the staged exe
(HKCU, `reg add`). The `run` target accepts a normal quit (exit 0 or 1) and fails on anything else, with
the code in hex.

## Modernization debt

The first port kept the MSVC 6 dialect alive with compiler switches. Removing each of these is a
follow-up step:

- `-fms-extensions -fasm-blocks`: `__declspec` and MS-style `__asm { }` blocks (`shp.c`,
  `shp_asm.c`, `d2.c` / `d3_engine.c` fill macros, ...). Replacing them with C makes the code portable
  beyond x86.
- `-Wno-error=incompatible-pointer-types`, `int-conversion`, `incompatible-function-pointer-types`,
  `return-mismatch`: loose typing from the decompilation. Together with `deprecated-non-prototype`
  these are ~11k warnings, hidden unless `GILDEGOLD_DEBT_WARNINGS=ON`.
- `-fno-strict-aliasing -fwrapv -fno-delete-null-pointer-checks`: type punning and other UB assumed safe.
- `-fno-auto-import`: needed because the asm blocks use every register.
- `--disable-dynamicbase`: fixed image base until the code is known to be ASLR-clean.
- `cmake/symbol-aliases.cmake`: one object reachable under several names (linker `alternatename`).
- About 230 function-pointer cast macros (`#define f ((type (*)(...))g)`, most marked `@original`) call
  a function through a prototype other than its own. Some depended on MSVC 6 code generation (for
  example `d2_PlaceMainWindow` relied on a tail jump to forward an undeclared argument). Each needs
  checking; it misbehaves silently, not at compile time.
- Asm that reads registers left over by its caller (`d2_ShpDarken16`'s `edx`/`esi`).
