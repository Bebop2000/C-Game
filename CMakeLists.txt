cmake_minimum_required(VERSION 3.10)
project(CGame)

file(GLOB_RECURSE SRC_FILES 
    ${CMAKE_SOURCE_DIR}/src/*.c 
    ${CMAKE_SOURCE_DIR}/src/scenes/*.c 
    ${CMAKE_SOURCE_DIR}/vendor/*.c)
file(GLOB_RECURSE H_FILES 
    ${CMAKE_SOURCE_DIR}/src/*.h 
    ${CMAKE_SOURCE_DIR}/src/scenes/*.h 
    ${CMAKE_SOURCE_DIR}/vendor/*.h)

#add_executable(CGame src/game/main.c ${SRC_FILES} ${H_FILES})
add_executable(CGame src/main.c src/stb_image.c ${SRC_FILES} ${H_FILES})

include_directories(src)
include_directories(src/blocks)
include_directories(src/scenes)
include_directories(src/vendor/glad)
include_directories(src/vendor)
include_directories(usr/include/GLFW)

find_package(OpenGL REQUIRED)
link_directories(${OPENGL_gl_LIBRARY})
#target_link_libraries(CGame PRIVATE m)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(CGame PUBLIC glfw OpenGL ${GLFW_LIBRARIES} ${CMAKE_DL_LIBS})
target_link_libraries(CGame PUBLIC m)
#link_directories(${glfw3})
#find_package(glfw3 REQUIRED)
#set(LIBS glfw3 opengl32)
