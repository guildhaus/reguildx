cmake_minimum_required(VERSION 3.25)

project(reguildx LANGUAGES C)

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
  message(FATAL_ERROR "reguildx is 32-bit only for now: configure with --toolchain cmake/llvm-mingw-i686.cmake")
endif()
if(NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
  message(WARNING "only clang (llvm-mingw) is tested")
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS ON)

file(GLOB REGUILDX_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable(reguildx WIN32 ${REGUILDX_SOURCES})
target_include_directories(reguildx PRIVATE include)

# Dialect crutches inherited from the MSVC 6 original. Each one is a modernization item to remove:
#   -fms-extensions                __declspec, MS-style __asm { } blocks (it enables them: no -fasm-blocks
#                                  needed), the i64 literal suffix
#   -fno-strict-aliasing -fwrapv   the code type-puns and relies on wrapping arithmetic
target_compile_options(reguildx PRIVATE
  -fms-extensions
  -fno-strict-aliasing
  -fwrapv
  -fno-delete-null-pointer-checks
  -fno-auto-import   # extern data is addressed directly (the asm blocks need every register)
  # Loose typing MSVC 6 accepted with a warning; modern clang rejects it by default.
  -Wno-error=incompatible-pointer-types
)
# The three warnings that make most of the build output are that same loose typing (~410 of them).
# Off by default so the rest (format, return-type, ...) stays readable; ON shows the debt.
option(REGUILDX_DEBT_WARNINGS "show the loose-typing warnings of the decompilation" OFF)
if(NOT REGUILDX_DEBT_WARNINGS)
  target_compile_options(reguildx PRIVATE
    -Wno-deprecated-non-prototype
    -Wno-incompatible-pointer-types
    -Wno-incompatible-function-pointer-types)
endif()

# The game was written against the DirectX 6/7 SDK: DirectInputCreate is gone from the default (8) dinput.h.
target_compile_definitions(reguildx PRIVATE DIRECTINPUT_VERSION=0x0700)

# Build options the original's units used.
option(REGUILDX_FIX_16BPP "16-bit back buffer in a window (dd_vesa)" OFF)
option(REGUILDX_FRAME_DUMP "frame dumps (dd_vesa, d3_d3d, shp, gfx, d2)" OFF)
foreach(_opt FIX_16BPP FRAME_DUMP)
  if(REGUILDX_${_opt})
    target_compile_definitions(reguildx PRIVATE REA_${_opt})
  endif()
endforeach()

# Miles Sound System: no import library ships with it; build one from the definition file.
if(NOT DLLTOOL)
  find_program(DLLTOOL NAMES llvm-dlltool i686-w64-mingw32-dlltool dlltool REQUIRED)
endif()
set(MSS32_DEF "${CMAKE_CURRENT_SOURCE_DIR}/third_party/mss32/mss32.def")
set(MSS32_LIB "${CMAKE_CURRENT_BINARY_DIR}/libmss32.a")
add_custom_command(
  OUTPUT "${MSS32_LIB}"
  COMMAND "${DLLTOOL}" -m i386 -d "${MSS32_DEF}" -l "${MSS32_LIB}"
  DEPENDS "${MSS32_DEF}"
  COMMENT "Building mss32 import library"
  VERBATIM)
add_custom_target(mss32_implib DEPENDS "${MSS32_LIB}")
add_dependencies(reguildx mss32_implib)

# Fixed base like the original (stable addresses for debugging; the code has not been audited for ASLR yet).
target_link_options(reguildx PRIVATE "LINKER:--disable-dynamicbase")

target_link_libraries(reguildx PRIVATE
  "${MSS32_LIB}"
  ddraw dinput dxguid strmiids
  ole32 winmm ws2_32 gdi32 user32 advapi32 kernel32
)

include(cmake/stage.cmake)
