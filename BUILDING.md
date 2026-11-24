# Building

The game builds with CMake and clang from [llvm-mingw](https://github.com/mstorsjo/llvm-mingw),
targeting 32-bit Windows (`i686-w64-mingw32`). The toolchain is self-contained (headers, CRT, DirectX
import libraries), so no Visual Studio, Windows SDK or DirectX SDK is needed. It also cross-compiles from
Linux or macOS.

## Requirements

- CMake >= 3.25 and Ninja
- llvm-mingw (tested: 20261117, clang 23.1). Any host build works (`ucrt-x86_64` on Windows).

## Build and run

CMake builds the game and stages a run directory; CLion runs and debugs it.

```sh
cmake --preset play                      # once: configure (the plain preset likewise)
cmake --build --preset play              # build only -> build-cmake/play/reguildx.exe
cmake --build --preset play -t stage     # build and stage build-cmake/play/run
```

Each build directory stages its own run directory (`build-cmake/plain/run`, `build-cmake/play/run`), with
its own `game.ini`. In CLion, the presets show up as CMake profiles, and two shared run configurations
(`.idea/runConfigurations/`) build the `stage` target and start the staged `GildeGold.exe` there:

| run configuration | profile | starts |
|---|---|---|
| `fullscreen` | `plain` | `build-cmake/plain/run/GildeGold.exe FULLSCREEN` |
| `windowed`   | `play`  | `build-cmake/play/run/GildeGold.exe DIRECTWINDOW` |

Run starts the game, Debug starts it under CLion's bundled GDB (64-bit, debugs the 32-bit game fine). A
CLion toolchain with all tools bundled is enough: the compiler comes from the CMake toolchain file. A
normal quit exits with 1.

| preset  | options                                                                   |
|---------|---------------------------------------------------------------------------|
| `plain` | none: the game as the original builds it (garbled in a window on a 32-bit desktop) |
| `play`  | `REGUILDX_FIX_16BPP` (16-bit back buffer in a window), `REGUILDX_FRAME_DUMP` |

Cache variables, all with defaults:

| variable | default |
|---|---|
| `LLVM_MINGW_ROOT` | the `LLVM_MINGW_ROOT` environment variable, else the newest `C:/Tools/llvm-mingw-*-x86_64`, else `PATH` |
| `REGUILDX_GAME_DIR` | `C:/Program Files/GOG Galaxy/Games/The Guild Gold` (the install, never written) |
| `REGUILDX_RUN_DIR` | `run` in the build directory |
| `REGUILDX_DEBT_WARNINGS` | `OFF`: hides the ~410 loose-typing warnings (see below) |

Staging (`cmake/stage-run.cmake`, also the `stage` target) links the install's folders into the run
directory and copies its ini / dll / asi files once. The run directory's `game.ini` is its own copy and
is never rewritten: the options menu's settings are kept, and the window mode comes from the run
configuration's argument (`DIRECTWINDOW` or `FULLSCREEN`, which override the ini's `Bildmodus`). Delete
the file for a fresh copy of the install's. On
current Windows, DirectDraw only reports 16-bit display modes under the `DWM8And16BitMitigation`
compatibility layer, and without it the game exits during start-up. Staging sets it for the staged exe
(HKCU, `reg add`).

## Modernization debt

The first port kept the MSVC 6 dialect alive with compiler switches. Removing each of these is a
follow-up step:

- `-fms-extensions`: `__declspec`, MS-style `__asm { }` blocks and the `i64` literal suffix (`shp.c`,
  `shp_asm.c`, `d2.c` / `d3_engine.c` fill macros, ...). Replacing them with C makes the code portable
  beyond x86.
- `-Wno-error=incompatible-pointer-types`: 4 COM out-parameters passed as `void **` (`d3_d3d.c`,
  `Dd_vesa.c`).
- `-Wno-error=return-mismatch`: upstream keeps a bare `return;` in an `int` function where it matches the
  original's code (`cm_RunWedding`'s two guards, `@original`).
- Together with `incompatible-function-pointer-types` (232) and `deprecated-non-prototype`
  (175) these are ~410 warnings, hidden unless `REGUILDX_DEBT_WARNINGS=ON`.
- `-fno-strict-aliasing -fwrapv -fno-delete-null-pointer-checks`: type punning and other UB assumed safe.
- `-fno-auto-import`: needed because the asm blocks use every register.
- `--disable-dynamicbase`: fixed image base until the code is known to be ASLR-clean.
- About 230 function-pointer cast macros (`#define f ((type (*)(...))g)`, most marked `@original`) call
  a function through a prototype other than its own. Some depended on MSVC 6 code generation (for
  example `d2_PlaceMainWindow` relied on a tail jump to forward an undeclared argument). Each needs
  checking; it misbehaves silently, not at compile time.
- Asm that reads registers left over by its caller (`d2_ShpDarken16`'s `edx`/`esi`).
