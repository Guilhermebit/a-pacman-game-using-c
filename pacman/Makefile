# ABOUT:
# This Makefile is for building the PacMan game.
# It includes compiler settings, directory structure, and build targets.
#
# Project Details:
# - Name: PacMan Game
# - Version: 1.0
# - Author: Guilherme Bitencurt
# - Date: November 7, 2023
#
# Description:
# This Makefile is used to build three versions of the PacMan game:
# - `build` for development
# - `debug` for debugging with additional information
# - `release` for optimized production use
#
# Usage:
# - OBS: Use mingw32-make for Windows
# - Linux/Mac:
# 	- Run `make all` to build all versions.
# 	- Run `make build`, `make debug`, or `make release` to build a specific version.
# 	- Run `make build-run`, `make debug-run`, or `make release-run` to build and run a specific version.
# 	- Run `make clean` to remove all build artifacts.
# 	- Run `make clean-build`, `make clean-debug`, or `make clean-release` to remove artifacts for a specific version.
#
# Note:
# You can customize compiler flags, source files, and other settings as needed.
####################################################################################################################

# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall -Wextra
DEBUG_CFLAGS := -g -DDEBUG  
RELEASE_CFLAGS := -O3 -DNDEBUG

# Directories
BUILD_DIR := build
DEBUG_DIR := debug
RELEASE_DIR := release
SRC_DIR := src

# Target executables
BUILD_EXECUTABLE := $(BUILD_DIR)/build_pacman.exe
DEBUG_EXECUTABLE := $(DEBUG_DIR)/debug_pacman.exe
RELEASE_EXECUTABLE := $(RELEASE_DIR)/release_pacman.exe

# Source files (list all your .c files)
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Object files (generated in the respective directories)
BUILD_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
DEBUG_OBJS := $(patsubst $(SRC_DIR)/%.c, $(DEBUG_DIR)/%.o, $(SRC_FILES))
RELEASE_OBJS := $(patsubst $(SRC_DIR)/%.c, $(RELEASE_DIR)/%.o, $(SRC_FILES))

# Detect the current platform 

# Windows
ifeq ($(OS), Windows_NT)
	CREATE_BUILD_DIR := if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	CREATE_DEBUG_DIR := if not exist $(DEBUG_DIR) mkdir $(DEBUG_DIR)
	CREATE_RELEASE_DIR := if not exist $(RELEASE_DIR) mkdir $(RELEASE_DIR)
	RM_BUILD := if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	RM_DEBUG := if exist $(DEBUG_DIR) rmdir /s /q $(DEBUG_DIR)
	RM_RELEASE := if exist $(RELEASE_DIR) rmdir /s /q $(RELEASE_DIR)
else
	CREATE_BUILD_DIR := if [ ! -d "$(BUILD_DIR)" ]; then mkdir -p "$(BUILD_DIR)"; fi
	CREATE_DEBUG_DIR := if [ ! -d "$(DEBUG_DIR)" ]; then mkdir -p "$(DEBUG_DIR)"; fi
	CREATE_RELEASE_DIR := if [ ! -d "$(RELEASE_DIR)" ]; then mkdir -p "$(RELEASE_DIR)"; fi
	RM_BUILD := if [ -d "$(BUILD_DIR)" ]; then rm -rf "$(BUILD_DIR)"; fi
	RM_DEBUG := if [ -d "$(DEBUG_DIR)" ]; then rm -rf "$(DEBUG_DIR)"; fi
	RM_RELEASE := if [ -d "$(RELEASE_DIR)" ]; then rm -rf "$(RELEASE_DIR)"; fi
endif

build: $(BUILD_EXECUTABLE)

debug: $(DEBUG_EXECUTABLE)

release: $(RELEASE_EXECUTABLE)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CREATE_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	$(CREATE_DEBUG_DIR)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -c $< -o $@ 

$(RELEASE_DIR)/%.o: $(SRC_DIR)/%.c
	$(CREATE_RELEASE_DIR)
	$(CC) $(CFLAGS) $(RELEASE_CFLAGS) -c $< -o $@  

# Link object files to create the final executables
$(BUILD_EXECUTABLE): $(BUILD_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(DEBUG_EXECUTABLE): $(DEBUG_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(RELEASE_EXECUTABLE): $(RELEASE_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Run the executables
build-run: build
ifeq ($(OS), Windows_NT)
	.\$(BUILD_DIR)\build_pacman.exe
else
	./$(BUILD_DIR)/build_pacman.exe
endif

debug-run: debug
ifeq ($(OS), Windows_NT)
	.\$(DEBUG_DIR)\debug_pacman.exe
else
	./$(DEBUG_DIR)/debug_pacman.exe
endif

release-run: release
ifeq ($(OS), Windows_NT)
	.\$(RELEASE_DIR)\release_pacman.exe
else
	./$(RELEASE_DIR)/release_pacman.exe
endif

# Clean all build artifacts
clean:
	$(RM_BUILD)
	$(RM_DEBUG)
	$(RM_RELEASE)

# Clean specific build artifacts
clean-build:
	$(RM_BUILD)

clean-debug:
	$(RM_DEBUG)

clean-release:
	$(RM_RELEASE)

# Default target
all: build debug release

.PHONY: all build debug release clean clean-build clean-debug clean-release build-run debug-run release-run