# Toolchain file: clang + lld from llvm-mingw, targeting 32-bit Windows (i686-w64-mingw32).
#
#   cmake -B build-cmake -G Ninja --toolchain cmake/llvm-mingw-i686.cmake -DLLVM_MINGW_ROOT=C:/Tools/llvm-mingw-...
#
# Works the same as a cross toolchain on Linux/macOS (point LLVM_MINGW_ROOT at the llvm-mingw there).

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR i686)

set(_default "$ENV{LLVM_MINGW_ROOT}")
if(NOT _default AND CMAKE_HOST_WIN32)
  file(GLOB _found "C:/Tools/llvm-mingw-*-x86_64")  # the newest one
  if(_found)
    list(SORT _found ORDER DESCENDING)
    list(GET _found 0 _default)
  endif()
endif()
set(LLVM_MINGW_ROOT "${_default}" CACHE PATH "llvm-mingw installation directory (empty: from PATH)")
if(LLVM_MINGW_ROOT)
  set(_bin "${LLVM_MINGW_ROOT}/bin/")
else()
  set(_bin "")  # from PATH
endif()

if(CMAKE_HOST_WIN32)
  set(_exe ".exe")
else()
  set(_exe "")
endif()

set(_triple i686-w64-mingw32)
set(CMAKE_C_COMPILER   "${_bin}${_triple}-clang${_exe}")
set(CMAKE_CXX_COMPILER "${_bin}${_triple}-clang++${_exe}")
set(CMAKE_RC_COMPILER  "${_bin}${_triple}-windres${_exe}")
set(CMAKE_AR           "${_bin}llvm-ar${_exe}" CACHE FILEPATH "")
set(CMAKE_RANLIB       "${_bin}llvm-ranlib${_exe}" CACHE FILEPATH "")
set(DLLTOOL            "${_bin}llvm-dlltool${_exe}" CACHE FILEPATH "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
