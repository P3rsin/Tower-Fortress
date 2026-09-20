# Tower Fortress

**Tower Fortress** is an in-progress 2D game project built in C++17 with [raylib](https://www.raylib.com/).

The project is currently focused on building the game's core systems while giving me experience designing and maintaining a larger, multi-file C++ codebase.

## Current Features

- Tile-based map loading from text data
- Data-driven tile properties, including color and solidity
- Player movement with acceleration, deceleration, and speed limits
- Frame-rate-independent movement using delta time
- Axis-separated collision detection and resolution against solid tiles
- Debug overlays for player state, map tiles, and collision checks
- CMake build system with automatic raylib retrieval through `FetchContent`

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

Run from the project root:

```bash
./build/TowerFortress
```

Running from the project root is currently required because the game loads map data from `assets/mapdata.txt` using a relative path.

## Controls

```text
W / A / S / D    Move player
```

## Project Structure

```text
Tower-Fortress/
├── assets/
│   └── mapdata.txt
├── src/
│   ├── debug/
│   │   ├── Debug.cpp
│   │   └── Debug.h
│   ├── player/
│   │   ├── Player.cpp
│   │   └── Player.h
│   ├── world/
│   │   ├── Map.cpp
│   │   ├── Map.h
│   │   ├── Tile.cpp
│   │   └── Tile.h
│   ├── GameConfig.h
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

## Status

Tower Fortress is under active development. The current version is an early prototype centered on movement, tile-map handling, collision behavior, debugging tools, and general code organization.

Additional gameplay systems and more robust map and collision handling will be added as the project develops.

## Author

**Haroon Awan**

[GitHub](https://github.com/P3rsin)
