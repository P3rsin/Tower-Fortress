# Tower Fortress

**Tower Fortress** is an in-progress 2D platformer built in C++17 with [raylib](https://www.raylib.com/).

The project is currently centered on building a reliable movement, collision, and tile-map foundation while giving me experience organizing and maintaining a multi-file C++ codebase.

## Current Features

- Text-based tile-map loading
- Data-driven tile properties, including color and solidity
- Horizontal movement with acceleration, deceleration, and a maximum speed
- Reduced horizontal acceleration while airborne
- Variable-height jumping:
  - press `K` to jump
  - hold `K` for a higher jump
  - release `K` early for a shorter jump
- Gravity and maximum fall speed
- Frame-rate-independent movement using delta time
- Delta-time clamping to reduce the effect of large frame hitches
- Axis-separated X/Y collision detection and resolution against solid tiles
- Collision handling against map boundaries
- Ground and ceiling collision state tracking
- Debug overlays for player position, velocity, map tiles, and collision checks
- CMake build system with automatic raylib retrieval through `FetchContent`

## Controls

| Input | Action |
| --- | --- |
| `A` | Move left |
| `D` | Move right |
| `K` | Jump / hold for increased jump height |

## Build

### Requirements

- CMake 3.24 or newer
- A C++17-compatible compiler
- Git and internet access during initial configuration so CMake can retrieve raylib

Configure and build from the project root:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Run:

```bash
./build/TowerFortress
```

> The executable should currently be launched from the project root because the map is loaded from `assets/mapdata.txt` using a relative path.

## Tile Map Format

The current map is an `18 x 12` grid stored in `assets/mapdata.txt`. Each tile is represented by a two-digit ID separated by spaces.

Example:

```text
01 01 01 01 01
01 01 00 01 01
00 00 00 00 00
```

Current tile IDs:

| ID | Behavior |
| --- | --- |
| `00` | Solid |
| `01` | Non-solid |

Tile properties are defined in `GameConfig.h`, allowing tile behavior and appearance to be looked up from the tile ID.

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

## Current Development Focus

The current prototype is primarily a test bed for platforming mechanics. Development is focused on making player movement and tile collision predictable before adding larger gameplay systems.

Current areas of work include:

- tuning acceleration, air control, gravity, and jump feel
- improving variable-height jumping
- testing edge, corner, ceiling, and landing collisions
- making collision resolution more robust when multiple solid tiles are involved
- improving map parsing and validation
- separating temporary debugging behavior from production game logic

## Status

Tower Fortress is in early development. The core movement and collision systems are functional but are still being refined, and the project should currently be treated as a gameplay and engine prototype rather than a complete game.

## Author

**Haroon Awan**

[GitHub](https://github.com/P3rsin)
