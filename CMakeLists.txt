cmake_minimum_required(VERSION 3.10)
project(CGame)

file(GLOB_RECURSE ENGINE_SRC_FILES src/engine/src/*.c)
file(GLOB_RECURSE ENGINE_BLOCK_SRC_FILES src/engine/src/blocks/*.c)
file(GLOB_RECURSE GAME_SRC_FILES src/game/scenes/*.c)


add_executable(CGame src/game/main.c ${ENGINE_SRC_FILES} ${ENGINE_BLOCK_SRC_FILES} ${GAME_SRC_FILES})
target_include_directories(CGame PUBLIC srs/engine/src src/engine/src/blocks src/game/scenes)