# Stages the run directory (cmake -P; called by the stage target, cmake/stage.cmake).
#
#   -DGAME_DIR=<the install>  -DRUN_DIR=<the run directory>  -DEXE=<the built exe>
#
# The install is never written: its folders are linked (junctions), its ini / dll / asi files copied once.
# game.ini is the run's own copy, never rewritten: the game's options menu changes it, the run configuration's
# FULLSCREEN / DIRECTWINDOW argument overrides its window mode. Delete RUN_DIR/game.ini for a fresh copy.

foreach(_v GAME_DIR RUN_DIR EXE)
  if(NOT DEFINED ${_v})
    message(FATAL_ERROR "stage-run: ${_v} not set")
  endif()
endforeach()
if(NOT EXISTS "${GAME_DIR}/GildeGold.exe")
  message(FATAL_ERROR "stage-run: no GildeGold.exe in '${GAME_DIR}' (set REGUILDX_GAME_DIR)")
endif()

file(MAKE_DIRECTORY "${RUN_DIR}")

# the install's folders, linked
file(GLOB _entries LIST_DIRECTORIES true "${GAME_DIR}/*")
foreach(_e IN LISTS _entries)
  if(IS_DIRECTORY "${_e}")
    get_filename_component(_name "${_e}" NAME)
    set(_link "${RUN_DIR}/${_name}")
    if(NOT EXISTS "${_link}" AND NOT IS_SYMLINK "${_link}")
      if(CMAKE_HOST_WIN32)
        file(TO_NATIVE_PATH "${_link}" _nl)
        file(TO_NATIVE_PATH "${_e}" _ne)
        execute_process(COMMAND cmd /c mklink /J "${_nl}" "${_ne}" OUTPUT_QUIET RESULT_VARIABLE _rc)
        if(_rc)
          message(FATAL_ERROR "stage-run: cannot link ${_link}")
        endif()
      else()
        file(CREATE_LINK "${_e}" "${_link}" SYMBOLIC)
      endif()
    endif()
  endif()
endforeach()

# its loose files, copied once (the run keeps its own game.ini)
foreach(_pattern "*.ini" "*.dll" "*.asi" "*.as6" "*.def" "*.sdb" "*.info")
  file(GLOB _files "${GAME_DIR}/${_pattern}")
  foreach(_f IN LISTS _files)
    get_filename_component(_name "${_f}" NAME)
    if(NOT EXISTS "${RUN_DIR}/${_name}")
      file(COPY_FILE "${_f}" "${RUN_DIR}/${_name}")
    endif()
  endforeach()
endforeach()

file(COPY_FILE "${EXE}" "${RUN_DIR}/GildeGold.exe" ONLY_IF_DIFFERENT)

# current Windows reports 16-bit display modes only under this compatibility layer (else the game exits at start)
if(CMAKE_HOST_WIN32)
  set(_key "HKCU\\Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers")
  set(_layers "DWM8And16BitMitigation HIGHDPIAWARE")
  file(TO_NATIVE_PATH "${RUN_DIR}/GildeGold.exe" _exe)
  execute_process(COMMAND reg query "${_key}" /v "${_exe}" OUTPUT_VARIABLE _q ERROR_QUIET)
  if(NOT _q MATCHES "REG_SZ +${_layers}")
    execute_process(COMMAND reg add "${_key}" /v "${_exe}" /t REG_SZ /d "${_layers}" /f OUTPUT_QUIET RESULT_VARIABLE _rc)
    if(_rc)
      message(WARNING "stage-run: could not set the compatibility layer for ${_exe}")
    else()
      message(STATUS "compatibility layer set: ${_exe} -> ${_layers}")
    endif()
  endif()
endif()
