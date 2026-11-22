# The stage target: build, then stage the run directory against the game install. The game is started
# from there by CLion's run configuration (.idea/runConfigurations/GildeGold.xml), not by CMake.

set(REGUILDX_GAME_DIR "C:/Program Files/GOG Galaxy/Games/The Guild Gold" CACHE PATH
    "the game install (GildeGold.exe, Data, gfx, ...); never written")
set(REGUILDX_RUN_DIR "${CMAKE_BINARY_DIR}/run" CACHE PATH
    "the run directory (one per build directory): links to the install, its own game.ini")

add_custom_target(stage
  COMMAND "${CMAKE_COMMAND}" -DGAME_DIR=${REGUILDX_GAME_DIR} -DRUN_DIR=${REGUILDX_RUN_DIR}
          "-DEXE=$<TARGET_FILE:reguildx>" -P "${CMAKE_SOURCE_DIR}/cmake/stage-run.cmake"
  DEPENDS reguildx
  COMMENT "Staging ${REGUILDX_RUN_DIR}"
  VERBATIM)
