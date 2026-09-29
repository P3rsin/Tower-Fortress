# Tower Fortress

**Tower Fortress** is an in-progress 2D tile-based platformer built in **C++17** with **raylib**.

The project is primarily a hands-on software engineering and game-development project. Current development has focused on building reusable systems for player movement, tile collision, map loading and rendering, camera control, and an integrated map editor.

## Current Features

### Player Movement

- Horizontal acceleration and deceleration
- Reduced acceleration and deceleration while airborne
- Maximum horizontal and falling speeds
- Gravity-based vertical movement
- Variable-height jumping
  - Press `K` to jump
  - Hold `K` for a higher jump
  - Release `K` early for a shorter jump
- Coyote time
- Jump buffering
- Frame-rate-independent movement using delta time
- Delta-time clamping to reduce the effect of large frame hitches

### Collision

- Axis-separated horizontal and vertical collision resolution
- Collision against solid map tiles
- Projected-position collision checks
- Nearest blocking-surface selection when multiple tiles overlap the player's projected position
- Collision against world boundaries
- Ground and ceiling state tracking
- Collision checks limited to nearby tiles rather than scanning the entire map

### Tile Maps

- Text-based tile-map loading
- Map dimensions determined from map data
- Tile IDs mapped to rendering and collision properties
- Data-driven tile solidity
- Maps stored internally as a one-dimensional row-major tile array
- Maps can be substantially larger than the game window
- Multiple map files can be loaded using the same map system

### Tilesheet Rendering

- Tile rendering from a single raylib `Texture2D`
- Individual tile graphics defined using source rectangles within a tilesheet
- Tile IDs used to look up both sprite and collision properties
- 16x16 source sprites scaled into the game's 100x100 world tiles
- Only tiles inside the camera's visible region are submitted for rendering

### Camera System

- Dedicated `CameraController`
- Player-following camera
- Camera clamping at map boundaries
- Zoom-aware visible-area calculations
- Independent free-camera controls for map editing
- Adjustable editor zoom
- Separation between world-space rendering and screen-space UI

### Map Editor

Tower Fortress includes an in-game map editor that is currently under active development.

The current editor supports:

- Switching between normal gameplay and editor mode
- Independent camera movement while editing
- Camera zooming
- Converting mouse screen coordinates into world and tile coordinates
- Selecting individual tiles
- Extending a selection into rectangular regions
- Visual highlighting of the selected region
- Displaying selected tile coordinates
- Map serialization support for writing tile IDs back to a text file

The visual tile palette and direct painting workflow are still being developed.

## Controls

### Gameplay

| Input | Action |
| --- | --- |
| `A` | Move left |
| `D` | Move right |
| `K` | Jump |
| Hold `K` | Sustain jump for additional height |
| `Y` | Enter map editor |

### Map Editor

| Input | Action |
| --- | --- |
| `W` | Move camera up |
| `A` | Move camera left |
| `S` | Move camera down |
| `D` | Move camera right |
| `Q` | Zoom out |
| `E` | Zoom in |
| Left Click | Select a tile |
| `Shift` + Left Click | Extend the current selection |
| `Y` | Return to gameplay |

Editor zoom is currently limited to a range of `0.4x` to `2.0x`.

## Build

### Requirements

- CMake 3.24 or newer
- A C++17-compatible compiler
- Git and internet access during initial configuration

raylib 6.0 is downloaded automatically through CMake using `FetchContent`.

### Configure and Build

From the project root:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Run:

```bash
./build/TowerFortress
```

The game should currently be launched from the project root because assets are loaded using relative paths such as:

```text
assets/map-one.txt
assets/desert-ruins.png
```

### Compiler Warnings

For GCC and Clang, the project enables:

```text
-Wall
-Wextra
-Wpedantic
```

to help catch common errors and questionable code during development.

## Project Structure

```text
Tower-Fortress/
├── assets/
│   ├── desert-ruins.png
│   ├── map-one.txt
│   ├── map-two.txt
│   ├── savedMap.txt
│   ├── soliditycheckmap.txt
│   └── tile-id-guide.png
│
├── src/
│   ├── camera/
│   │   ├── CameraController.cpp
│   │   └── CameraController.h
│   │
│   ├── editor/
│   │   ├── MapEditor.cpp
│   │   └── MapEditor.h
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
│   ├── GameState.h
│   └── main.cpp
│
├── CMakeLists.txt
└── README.md
```

## Architecture

The project is divided into several small systems with separate responsibilities.

### `Player`

Responsible for:

- Player position and dimensions
- Horizontal acceleration and deceleration
- Gravity and jumping
- Coyote time
- Jump buffering
- Horizontal and vertical collision resolution
- Player rendering

Player collision is resolved independently along the X and Y axes.

For each projected movement step, the player determines the nearby tiles that could participate in a collision and selects the nearest valid blocking surface before correcting its position.

### `Map`

Responsible for:

- Loading map data from text files
- Determining map width and height
- Constructing and storing tiles
- Owning the tilesheet texture
- Retrieving tiles by grid coordinate
- Modifying tile IDs
- Determining which tiles are visible to the camera
- Rendering visible tiles

`Map` owns its raylib texture resource and releases it through its destructor.

Copy construction and copy assignment are disabled to prevent multiple `Map` objects from attempting to manage the same texture resource.

### `Tile`

Each `Tile` stores only:

- Its tile ID
- Its world-space rectangle

Rendering and collision properties are not duplicated inside every tile.

Instead, a tile uses its ID to access the shared `TILE_PROPERTIES` lookup table.

### `CameraController`

Responsible for:

- Owning the raylib `Camera2D`
- Following the player during gameplay
- Preventing the gameplay camera from exposing areas beyond the map
- Providing independent free movement in editor mode
- Managing editor zoom

This keeps camera behavior separate from both the player and map systems.

### `MapEditor`

Responsible for editor-specific interaction and state.

It currently maintains:

- A reference to the map being edited
- The current tile selection
- Mouse-to-world coordinate conversion
- Rectangular selection behavior
- Selection rendering
- Editor UI
- Map serialization support

The editor references the existing `Map` rather than duplicating map dimensions, tiles, or texture resources.

### `GameState`

The application currently switches between two states:

```cpp
enum class GameState
{
    PlayerFocused,
    MapEditor
};
```

This keeps gameplay input and editor input from running simultaneously.

### `GameConfig`

Contains shared constants and configuration, including:

- Window dimensions
- World tile dimensions
- Player movement timing constants
- Custom colors
- Tilesheet dimensions
- Tile source-rectangle generation
- The tile-property lookup table

## Tile Properties

Tile behavior and appearance are defined using:

```cpp
struct TileProperties
{
    Rectangle sourceRect;
    bool isSolid;
};
```

The index of `TILE_PROPERTIES` corresponds directly to the tile ID.

For example:

```text
Tile ID
   |
   v
TILE_PROPERTIES[id]
   |
   +------> source rectangle
   |
   +------> solidity
```

This allows map files to store only integer tile IDs while rendering and gameplay behavior are defined centrally.

The current tileset defines 72 tile IDs.

## Tile Map Format

Maps are currently represented as text files containing two-digit tile IDs separated by spaces.

Example:

```text
08 08 08 08 08
08 32 32 33 08
08 32 30 33 08
00 00 00 00 00
```

Each number corresponds to an index in `TILE_PROPERTIES`.

The loader converts these IDs into `Tile` objects positioned within the world grid.

### Current Parser Limitation

The parser currently assumes:

- Every tile ID contains exactly two characters
- Tile IDs are separated by exactly one character
- The current separator is a space

Because the loader relies on fixed character offsets, map parsing is still more format-dependent than intended.

Replacing the fixed-width parser with token-based integer parsing is a planned cleanup task.

## Rendering Pipeline

World objects are rendered inside raylib's `BeginMode2D()` / `EndMode2D()` block:

```text
BeginDrawing
    |
    +-- BeginMode2D(camera)
    |      |
    |      +-- Map
    |      +-- Map Editor overlays
    |      +-- Player
    |
    +-- EndMode2D
    |
    +-- Screen-space editor UI
    |
EndDrawing
```

This keeps world coordinates independent from screen coordinates.

The map calculates the visible world area using the camera target, offset, and zoom, converts that region into tile coordinates, and renders only the relevant portion of the map.

## Tilesheet

The current tilesheet is:

```text
assets/desert-ruins.png
```

Rather than creating an individual texture for every tile, the entire tilesheet is loaded once.

Each tile property contains a `Rectangle` describing the corresponding 16x16 region of the tilesheet.

raylib's `DrawTexturePro()` then scales that source rectangle into the tile's world-space destination rectangle.

```text
desert-ruins.png
       |
       v
single Texture2D
       |
       +-- source rectangle for tile 0
       +-- source rectangle for tile 1
       +-- source rectangle for tile 2
       +-- ...
       |
       v
DrawTexturePro()
       |
       v
100x100 world tile
```

## Current Development State

Tower Fortress is currently an engine/gameplay prototype rather than a finished game.

The project now has functional foundations for:

```text
Player Movement
       +
Tile Collision
       +
Text-Based Maps
       +
Tilesheet Rendering
       +
Large Scrollable Worlds
       +
Camera Control
       +
In-Game Map Editing
```

Recent development has focused heavily on refactoring the codebase so that the editor, camera, map, player, and application state have clearer responsibilities before additional gameplay systems are introduced.

## Current Priorities

Near-term development includes:

- Finishing the visual tile palette
- Allowing selected tiles to be painted directly into the map
- Improving map saving and loading
- Replacing fixed-width map parsing with token-based parsing
- Improving editor usability
- Continuing code cleanup and consistency improvements
- Adding player sprites and animation
- Building more complete levels using the editor

Later systems may include:

- Hazards
- Moving platforms
- Enemies
- Interactive objects
- Level transitions
- Audio
- Additional game states

## Purpose

Tower Fortress is being developed both as a game and as a way to practice larger-scale C++ software development.

The project has provided experience with:

- Object-oriented organization
- Multi-file C++ projects
- Resource ownership
- References and const-correctness
- CMake
- Git workflows
- Collision detection and resolution
- Coordinate systems
- Camera transformations
- Texture atlases
- File parsing and serialization
- Interactive development tooling
- Refactoring evolving code
- Separating responsibilities across systems

## Author

**Haroon Awan**

GitHub: [P3rsin](https://github.com/P3rsin)
