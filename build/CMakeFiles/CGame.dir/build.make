# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/doug/C-Game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/doug/C-Game/build

# Include any dependencies generated for this target.
include CMakeFiles/CGame.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CGame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CGame.dir/flags.make

CMakeFiles/CGame.dir/src/game/main.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/game/main.c.o: ../src/game/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CGame.dir/src/game/main.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/game/main.c.o   -c /home/doug/C-Game/src/game/main.c

CMakeFiles/CGame.dir/src/game/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/game/main.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/game/main.c > CMakeFiles/CGame.dir/src/game/main.c.i

CMakeFiles/CGame.dir/src/game/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/game/main.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/game/main.c -o CMakeFiles/CGame.dir/src/game/main.c.s

CMakeFiles/CGame.dir/src/engine/src/stb_image.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/engine/src/stb_image.c.o: ../src/engine/src/stb_image.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/CGame.dir/src/engine/src/stb_image.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/engine/src/stb_image.c.o   -c /home/doug/C-Game/src/engine/src/stb_image.c

CMakeFiles/CGame.dir/src/engine/src/stb_image.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/engine/src/stb_image.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/engine/src/stb_image.c > CMakeFiles/CGame.dir/src/engine/src/stb_image.c.i

CMakeFiles/CGame.dir/src/engine/src/stb_image.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/engine/src/stb_image.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/engine/src/stb_image.c -o CMakeFiles/CGame.dir/src/engine/src/stb_image.c.s

CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.o: ../src/engine/src/blocks/block.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.o   -c /home/doug/C-Game/src/engine/src/blocks/block.c

CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/engine/src/blocks/block.c > CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.i

CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/engine/src/blocks/block.c -o CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.s

CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.o: ../src/engine/src/blocks/blockTextures.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.o   -c /home/doug/C-Game/src/engine/src/blocks/blockTextures.c

CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/engine/src/blocks/blockTextures.c > CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.i

CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/engine/src/blocks/blockTextures.c -o CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.s

CMakeFiles/CGame.dir/src/engine/src/camera.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/engine/src/camera.c.o: ../src/engine/src/camera.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/CGame.dir/src/engine/src/camera.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/engine/src/camera.c.o   -c /home/doug/C-Game/src/engine/src/camera.c

CMakeFiles/CGame.dir/src/engine/src/camera.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/engine/src/camera.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/engine/src/camera.c > CMakeFiles/CGame.dir/src/engine/src/camera.c.i

CMakeFiles/CGame.dir/src/engine/src/camera.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/engine/src/camera.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/engine/src/camera.c -o CMakeFiles/CGame.dir/src/engine/src/camera.c.s

CMakeFiles/CGame.dir/src/engine/src/chunk.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/engine/src/chunk.c.o: ../src/engine/src/chunk.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/CGame.dir/src/engine/src/chunk.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/engine/src/chunk.c.o   -c /home/doug/C-Game/src/engine/src/chunk.c

CMakeFiles/CGame.dir/src/engine/src/chunk.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/engine/src/chunk.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/engine/src/chunk.c > CMakeFiles/CGame.dir/src/engine/src/chunk.c.i

CMakeFiles/CGame.dir/src/engine/src/chunk.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/engine/src/chunk.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/engine/src/chunk.c -o CMakeFiles/CGame.dir/src/engine/src/chunk.c.s

CMakeFiles/CGame.dir/src/engine/src/input.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/engine/src/input.c.o: ../src/engine/src/input.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/CGame.dir/src/engine/src/input.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/engine/src/input.c.o   -c /home/doug/C-Game/src/engine/src/input.c

CMakeFiles/CGame.dir/src/engine/src/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/engine/src/input.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/engine/src/input.c > CMakeFiles/CGame.dir/src/engine/src/input.c.i

CMakeFiles/CGame.dir/src/engine/src/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/engine/src/input.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/engine/src/input.c -o CMakeFiles/CGame.dir/src/engine/src/input.c.s

CMakeFiles/CGame.dir/src/engine/src/render.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/engine/src/render.c.o: ../src/engine/src/render.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/CGame.dir/src/engine/src/render.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/engine/src/render.c.o   -c /home/doug/C-Game/src/engine/src/render.c

CMakeFiles/CGame.dir/src/engine/src/render.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/engine/src/render.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/engine/src/render.c > CMakeFiles/CGame.dir/src/engine/src/render.c.i

CMakeFiles/CGame.dir/src/engine/src/render.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/engine/src/render.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/engine/src/render.c -o CMakeFiles/CGame.dir/src/engine/src/render.c.s

CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.o: ../src/engine/src/shaderProgram.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.o   -c /home/doug/C-Game/src/engine/src/shaderProgram.c

CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/engine/src/shaderProgram.c > CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.i

CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/engine/src/shaderProgram.c -o CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.s

CMakeFiles/CGame.dir/src/engine/src/texture.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/engine/src/texture.c.o: ../src/engine/src/texture.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/CGame.dir/src/engine/src/texture.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/engine/src/texture.c.o   -c /home/doug/C-Game/src/engine/src/texture.c

CMakeFiles/CGame.dir/src/engine/src/texture.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/engine/src/texture.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/engine/src/texture.c > CMakeFiles/CGame.dir/src/engine/src/texture.c.i

CMakeFiles/CGame.dir/src/engine/src/texture.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/engine/src/texture.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/engine/src/texture.c -o CMakeFiles/CGame.dir/src/engine/src/texture.c.s

CMakeFiles/CGame.dir/src/engine/src/window.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/engine/src/window.c.o: ../src/engine/src/window.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/CGame.dir/src/engine/src/window.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/engine/src/window.c.o   -c /home/doug/C-Game/src/engine/src/window.c

CMakeFiles/CGame.dir/src/engine/src/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/engine/src/window.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/engine/src/window.c > CMakeFiles/CGame.dir/src/engine/src/window.c.i

CMakeFiles/CGame.dir/src/engine/src/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/engine/src/window.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/engine/src/window.c -o CMakeFiles/CGame.dir/src/engine/src/window.c.s

CMakeFiles/CGame.dir/src/engine/vendor/glad.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/engine/vendor/glad.c.o: ../src/engine/vendor/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/CGame.dir/src/engine/vendor/glad.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/engine/vendor/glad.c.o   -c /home/doug/C-Game/src/engine/vendor/glad.c

CMakeFiles/CGame.dir/src/engine/vendor/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/engine/vendor/glad.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/engine/vendor/glad.c > CMakeFiles/CGame.dir/src/engine/vendor/glad.c.i

CMakeFiles/CGame.dir/src/engine/vendor/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/engine/vendor/glad.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/engine/vendor/glad.c -o CMakeFiles/CGame.dir/src/engine/vendor/glad.c.s

CMakeFiles/CGame.dir/src/game/scenes/testScene.c.o: CMakeFiles/CGame.dir/flags.make
CMakeFiles/CGame.dir/src/game/scenes/testScene.c.o: ../src/game/scenes/testScene.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/CGame.dir/src/game/scenes/testScene.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CGame.dir/src/game/scenes/testScene.c.o   -c /home/doug/C-Game/src/game/scenes/testScene.c

CMakeFiles/CGame.dir/src/game/scenes/testScene.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CGame.dir/src/game/scenes/testScene.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/doug/C-Game/src/game/scenes/testScene.c > CMakeFiles/CGame.dir/src/game/scenes/testScene.c.i

CMakeFiles/CGame.dir/src/game/scenes/testScene.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CGame.dir/src/game/scenes/testScene.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/doug/C-Game/src/game/scenes/testScene.c -o CMakeFiles/CGame.dir/src/game/scenes/testScene.c.s

# Object files for target CGame
CGame_OBJECTS = \
"CMakeFiles/CGame.dir/src/game/main.c.o" \
"CMakeFiles/CGame.dir/src/engine/src/stb_image.c.o" \
"CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.o" \
"CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.o" \
"CMakeFiles/CGame.dir/src/engine/src/camera.c.o" \
"CMakeFiles/CGame.dir/src/engine/src/chunk.c.o" \
"CMakeFiles/CGame.dir/src/engine/src/input.c.o" \
"CMakeFiles/CGame.dir/src/engine/src/render.c.o" \
"CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.o" \
"CMakeFiles/CGame.dir/src/engine/src/texture.c.o" \
"CMakeFiles/CGame.dir/src/engine/src/window.c.o" \
"CMakeFiles/CGame.dir/src/engine/vendor/glad.c.o" \
"CMakeFiles/CGame.dir/src/game/scenes/testScene.c.o"

# External object files for target CGame
CGame_EXTERNAL_OBJECTS =

CGame: CMakeFiles/CGame.dir/src/game/main.c.o
CGame: CMakeFiles/CGame.dir/src/engine/src/stb_image.c.o
CGame: CMakeFiles/CGame.dir/src/engine/src/blocks/block.c.o
CGame: CMakeFiles/CGame.dir/src/engine/src/blocks/blockTextures.c.o
CGame: CMakeFiles/CGame.dir/src/engine/src/camera.c.o
CGame: CMakeFiles/CGame.dir/src/engine/src/chunk.c.o
CGame: CMakeFiles/CGame.dir/src/engine/src/input.c.o
CGame: CMakeFiles/CGame.dir/src/engine/src/render.c.o
CGame: CMakeFiles/CGame.dir/src/engine/src/shaderProgram.c.o
CGame: CMakeFiles/CGame.dir/src/engine/src/texture.c.o
CGame: CMakeFiles/CGame.dir/src/engine/src/window.c.o
CGame: CMakeFiles/CGame.dir/src/engine/vendor/glad.c.o
CGame: CMakeFiles/CGame.dir/src/game/scenes/testScene.c.o
CGame: CMakeFiles/CGame.dir/build.make
CGame: CMakeFiles/CGame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/doug/C-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking C executable CGame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CGame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CGame.dir/build: CGame

.PHONY : CMakeFiles/CGame.dir/build

CMakeFiles/CGame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CGame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CGame.dir/clean

CMakeFiles/CGame.dir/depend:
	cd /home/doug/C-Game/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/doug/C-Game /home/doug/C-Game /home/doug/C-Game/build /home/doug/C-Game/build /home/doug/C-Game/build/CMakeFiles/CGame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CGame.dir/depend

