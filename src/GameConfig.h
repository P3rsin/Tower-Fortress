#pragma once
#include <array>
#include <raylib.h>

// TILE AND WINDOW DIMENSIONS
constexpr int PURE_TILE_SIZE = 20;
constexpr int SCALE_FACTOR = 5;
constexpr int TILE_SIZE = PURE_TILE_SIZE * SCALE_FACTOR;

constexpr int WINDOW_TILE_WIDTH = 18;
constexpr int WINDOW_TILE_HEIGHT = 12;

constexpr int WINDOW_WIDTH = WINDOW_TILE_WIDTH * TILE_SIZE;
constexpr int WINDOW_HEIGHT = WINDOW_TILE_HEIGHT * TILE_SIZE;

// CUSTOM COLORS
constexpr Color BRIGHTYELLOW = {255, 220, 0, 255};

// MAP FILE PARSING - based on txt formatting used
constexpr std::size_t TILE_ID_LENGTH = 2;
constexpr std::size_t TILE_ID_SEPARATOR_LENGTH = 1;
constexpr std::size_t TILE_ID_STRIDE = TILE_ID_LENGTH + TILE_ID_SEPARATOR_LENGTH;

// PLAYER MOVEMENT
constexpr float COYOTE_TIME = 0.05f;
constexpr float JUMP_BUFFER_TIME = 0.05f;

// TILE PROPERTY LOOKUP TABLES - arrays indexed by tile ID
struct TileProperties
{
    Rectangle sourceRect;
    bool isSolid;
};

inline constexpr int TILE_SPRITE_SIZE = 16;
inline constexpr int TILE_SHEET_COLUMNS = 16;

constexpr Rectangle GetTileSourceRect(int sheetIndex)
{
    return Rectangle{
        static_cast<float>((sheetIndex % TILE_SHEET_COLUMNS) * TILE_SPRITE_SIZE),
        static_cast<float>((sheetIndex / TILE_SHEET_COLUMNS) * TILE_SPRITE_SIZE),
        static_cast<float>(TILE_SPRITE_SIZE),
        static_cast<float>(TILE_SPRITE_SIZE)};
}

// TILE PROPERTY LOOKUP TABLE
// Array index = your tile ID.
//
// Solidity assumptions:
// - walls, floors, ceilings, cave boundaries -> solid
// - empty space, fire, rubble/decorations, hanging pieces -> non-solid

inline constexpr std::array<TileProperties, 72> TILE_PROPERTIES = {

    // Sheet row 1
    TileProperties{GetTileSourceRect(17), true},  // tile ID 0
    TileProperties{GetTileSourceRect(18), true},  // tile ID 1
    TileProperties{GetTileSourceRect(19), true},  // tile ID 2
    TileProperties{GetTileSourceRect(20), true},  // tile ID 3
    TileProperties{GetTileSourceRect(21), true},  // tile ID 4
    TileProperties{GetTileSourceRect(22), true},  // tile ID 5
    TileProperties{GetTileSourceRect(23), true},  // tile ID 6

    // Sheet row 2
    TileProperties{GetTileSourceRect(33), true},  // tile ID 7
    TileProperties{GetTileSourceRect(34), false}, // tile ID 8 - empty/black
    TileProperties{GetTileSourceRect(35), true},  // tile ID 9
    TileProperties{GetTileSourceRect(36), true},  // tile ID 10
    TileProperties{GetTileSourceRect(37), true},  // tile ID 11
    TileProperties{GetTileSourceRect(38), false}, // tile ID 12 - fire/opening
    TileProperties{GetTileSourceRect(39), true},  // tile ID 13

    // Sheet row 3
    TileProperties{GetTileSourceRect(49), true},  // tile ID 14
    TileProperties{GetTileSourceRect(50), true},  // tile ID 15
    TileProperties{GetTileSourceRect(51), true},  // tile ID 16
    TileProperties{GetTileSourceRect(52), true},  // tile ID 17
    TileProperties{GetTileSourceRect(53), true},  // tile ID 18
    TileProperties{GetTileSourceRect(54), false}, // tile ID 19 - fire
    TileProperties{GetTileSourceRect(55), true},  // tile ID 20

    // Sheet row 4
    TileProperties{GetTileSourceRect(65), true},  // tile ID 21
    TileProperties{GetTileSourceRect(66), true},  // tile ID 22
    TileProperties{GetTileSourceRect(67), true},  // tile ID 23
    TileProperties{GetTileSourceRect(68), true},  // tile ID 24
    TileProperties{GetTileSourceRect(69), true},  // tile ID 25
    TileProperties{GetTileSourceRect(70), true},  // tile ID 26
    TileProperties{GetTileSourceRect(71), false}, // tile ID 27 - hanging rubble

    // Sheet row 5
    TileProperties{GetTileSourceRect(81), false}, // tile ID 28 - rubble/decor
    TileProperties{GetTileSourceRect(82), false}, // tile ID 29 - rubble/decor
    TileProperties{GetTileSourceRect(83), true},  // tile ID 30 - structure
    TileProperties{GetTileSourceRect(84), true},  // tile ID 31 - structure
    TileProperties{GetTileSourceRect(85), true},  // tile ID 32
    TileProperties{GetTileSourceRect(86), true},  // tile ID 33
    TileProperties{GetTileSourceRect(87), true},  // tile ID 34

    // Sheet row 6
    TileProperties{GetTileSourceRect(97), false}, // tile ID 35 - thin post/decor
    TileProperties{GetTileSourceRect(98), false}, // tile ID 36 - thin post/decor
    TileProperties{GetTileSourceRect(99), true},  // tile ID 37
    TileProperties{GetTileSourceRect(100), true}, // tile ID 38
    TileProperties{GetTileSourceRect(101), true}, // tile ID 39
    TileProperties{GetTileSourceRect(102), true}, // tile ID 40
    TileProperties{GetTileSourceRect(103), true}, // tile ID 41

    // Sheet row 8
    TileProperties{GetTileSourceRect(129), true}, // tile ID 42
    TileProperties{GetTileSourceRect(130), true}, // tile ID 43
    TileProperties{GetTileSourceRect(131), true}, // tile ID 44
    TileProperties{GetTileSourceRect(132), true}, // tile ID 45
    TileProperties{GetTileSourceRect(133), true}, // tile ID 46
    TileProperties{GetTileSourceRect(134), true}, // tile ID 47
    TileProperties{GetTileSourceRect(135), true}, // tile ID 48

    // Sheet row 9
    TileProperties{GetTileSourceRect(145), true},  // tile ID 49
    TileProperties{GetTileSourceRect(146), false}, // tile ID 50 - empty/black
    TileProperties{GetTileSourceRect(147), true},  // tile ID 51
    TileProperties{GetTileSourceRect(148), true},  // tile ID 52
    TileProperties{GetTileSourceRect(149), true},  // tile ID 53
    TileProperties{GetTileSourceRect(151), true},  // tile ID 54

    // Sheet row 10
    TileProperties{GetTileSourceRect(161), true}, // tile ID 55
    TileProperties{GetTileSourceRect(162), true}, // tile ID 56
    TileProperties{GetTileSourceRect(163), true}, // tile ID 57
    TileProperties{GetTileSourceRect(164), true}, // tile ID 58
    TileProperties{GetTileSourceRect(165), true}, // tile ID 59
    TileProperties{GetTileSourceRect(166), true}, // tile ID 60
    TileProperties{GetTileSourceRect(167), true}, // tile ID 61

    // Sheet row 11
    TileProperties{GetTileSourceRect(177), true},  // tile ID 62
    TileProperties{GetTileSourceRect(178), true},  // tile ID 63
    TileProperties{GetTileSourceRect(179), true},  // tile ID 64
    TileProperties{GetTileSourceRect(180), true},  // tile ID 65
    TileProperties{GetTileSourceRect(181), false}, // tile ID 66 - falling/decorative rock

    // Sheet row 12
    TileProperties{GetTileSourceRect(193), false}, // tile ID 67 - decoration
    TileProperties{GetTileSourceRect(194), false}, // tile ID 68 - decoration
    TileProperties{GetTileSourceRect(195), false}, // tile ID 69 - hanging/dripping decor
    TileProperties{GetTileSourceRect(196), false}, // tile ID 70 - hanging/dripping decor
    TileProperties{GetTileSourceRect(197), false}  // tile ID 71 - rubble/decor
};