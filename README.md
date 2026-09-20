# Tower Fortress

**Tower Fortress** is an in-progress 2D game project built in C++17 with raylib.

The project is currently in early development and is being used to build out the game's core systems while giving me experience working with a larger, multi-file C++ codebase.

## Current Features

- Tile-based map loading
- Player movement
- Basic tile collision detection
- Debug information and collision visualization
- CMake build system
- raylib integration through CMake

## Build

### Requirements

- CMake 3.24 or newer
- A C++17-compatible compiler
- Git and internet access during initial configuration so CMake can retrieve raylib

Configure and build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Run:

```bash
./build/TowerFortress
```

## Controls

```text
W / A / S / D    Move player
```

## Project Structure

```text
Tower-Fortress/
├── assets/
├── src/
│   ├── debug/
│   ├── player/
│   ├── world/
│   ├── GameConfig.h
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

## Status

Tower Fortress is under active development. The current implementation is an early prototype focused on movement, collision, map handling, and general project structure.

## Author

**Haroon Awan**

[GitHub](https://github.com/P3rsin)
