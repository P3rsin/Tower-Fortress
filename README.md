# Tower Fortress

**Tower Fortress** is an in-progress 2D platformer built in C++17 with [raylib](https://www.raylib.com/).

The project is currently focused on developing the underlying systems for a tile-based platformer while giving me experience designing and maintaining a multi-file C++ codebase. Current work includes player movement, tile collision, map loading, camera movement, and tilesheet-based rendering.

## Current Features

### Player Movement

- Horizontal acceleration and deceleration
- Reduced acceleration and deceleration while airborne
- Maximum horizontal and falling speeds
- Gravity-based vertical movement
- Variable-height jumping
  - press `K` to jump
  - hold `K` for a higher jump
  - release `K` early for a shorter jump
- Coyote time for slightly delayed jumps after leaving a platform
- Jump buffering for jump inputs made shortly before landing
- Frame-rate-independent movement using delta time
- Delta-time clamping to reduce the effect of large frame hitches

### Collision

- Axis-separated horizontal and vertical collision detection
- Collision against solid map tiles
- Nearest blocking-surface selection when multiple tiles overlap the player's projected position
- Collision against world boundaries
- Ground and ceiling collision state tracking
- Collision queries limited to tiles surrounding the player's projected position rather than the entire map

### Tile Map

- Text-based tile-map loading
- Map dimensions determined from the loaded map data
- Tile IDs mapped to gameplay and rendering properties
- Data-driven tile solidity
- Tile maps stored internally as a one-dimensional row-major tile array
- Maps can extend beyond the dimensions of the game window

### Rendering

- Tilesheet-based map rendering using a single raylib `Texture2D`
- Individual tile graphics selected using source rectangles within the tilesheet
- Tile IDs used to reference both sprite and solidity information
- 16x16 source sprites scaled to the game's world tile size
- Rendering limited to tiles within the camera's visible area

### Camera

- Player-following `Camera2D`
- Camera movement through maps larger than the viewport
- Camera clamping at map boundaries
- Separation between world-space rendering and screen-space UI

### Build System

- CMake build configuration
- C++17
- raylib 6.0 retrieved automatically through CMake `FetchContent`

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

Run from the project root:

```bash
./build/TowerFortress
```

The executable should currently be launched from the project root because assets are loaded using relative paths such as:

```text
assets/mapdata.txt
assets/desert-ruins.png
```

## Tile Map Format

Maps are stored as text files containing two-digit tile IDs separated by spaces.

Example:

```text
00 00 00 00 00
00 08 08 08 00
00 08 08 08 00
00 00 00 00 00
```

Each tile ID indexes the `TILE_PROPERTIES` table defined in `GameConfig.h`.

A tile property currently contains:

```cpp
struct TileProperties
{
    Rectangle sourceRect;
    bool isSolid;
};
```

This allows a tile ID to determine both:

- which portion of the tilesheet should be rendered;
- whether the tile participates in player collision.

The current test map is larger than the game window, allowing the camera and world-space movement systems to be tested.

### Current Parser Limitation

The current map parser expects each tile ID to:

- contain exactly two characters;
- be separated by one character, currently a space.

Map parsing and validation are still being developed and will eventually be made less dependent on fixed-width formatting.

## Tilesheet Rendering

The current tilesheet is:

```text
assets/desert-ruins.png
```

Tile graphics are stored in a single texture rather than loading a separate texture for every tile.

The source tiles are 16x16 pixels. `TILE_PROPERTIES` stores the appropriate source rectangle for each supported tile ID:

```cpp
TileProperties{GetTileSourceRect(...), true}
```

During rendering, the source rectangle is drawn into the tile's world-space destination rectangle using raylib's `DrawTexturePro()`.

Conceptually:

```text
Tile ID
   |
   v
TILE_PROPERTIES[id]
   |
   +----> solidity
   |
   +----> source rectangle
              |
              v
         tilesheet texture
              |
              v
       rendered world tile
```

## Camera and World Space

The map is independent of the game window size.

The player and tiles remain at their actual world coordinates while raylib's `Camera2D` determines which portion of the world is visible.

The camera follows the player while remaining constrained to the boundaries of the loaded map.

Only tiles within the camera's visible area are currently submitted for rendering.

## Project Structure

```text
Tower-Fortress/
├── assets/
│   ├── desert-ruins.png
│   └── mapdata.txt
│
├── src/
│   ├── debug/
│   │   ├── Debug.cpp
│   │   └── Debug.h
│   │
│   ├── player/
│   │   ├── Player.cpp
│   │   └── Player.h
│   │
│   ├── world/
│   │   ├── Map.cpp
│   │   ├── Map.h
│   │   ├── Tile.cpp
│   │   └── Tile.h
│   │
│   ├── GameConfig.h
│   └── main.cpp
│
├── CMakeLists.txt
└── README.md
```

## Architecture

The project is currently divided into several small systems.

### `Player`

Responsible for:

- player movement;
- velocity and acceleration;
- jumping;
- coyote time and jump buffering;
- collision detection and resolution;
- player rendering.

### `Map`

Responsible for:

- loading map data;
- storing map dimensions;
- constructing tiles;
- loading and unloading the tilesheet texture;
- retrieving tiles by grid position;
- determining the camera-visible tile range;
- rendering visible tiles.

### `Tile`

Stores the minimal per-tile state:

- tile ID;
- world-space rectangle.

Gameplay and visual properties are looked up from the tile ID rather than duplicated inside every tile instance.

### `GameConfig`

Contains shared configuration and tile definitions, including:

- tile and window dimensions;
- movement timing constants;
- tile source-rectangle generation;
- the tile-property lookup table.

## Current Development State

Tower Fortress is still an early gameplay and engine prototype rather than a complete game.

The project currently has a functional foundation for:

```text
player movement
       +
tile collision
       +
large tile maps
       +
camera movement
       +
tilesheet rendering
```

The player is still represented by a simple rectangle, and the current map primarily exists to test movement, collision, camera behavior, and rendering.

## Planned Development

Near-term areas of development include:

- improving map parsing and validation;
- cleaning up temporary debugging code;
- adding player sprites and animation;
- expanding level design beyond the current test map;
- refining camera behavior based on gameplay needs;
- introducing additional gameplay objects and mechanics.

More advanced systems such as enemies, hazards, moving platforms, level transitions, audio, and broader game-state management can be added once the current foundation is sufficiently stable.

## Author

**Haroon Awan**

[GitHub](https://github.com/P3rsin)
