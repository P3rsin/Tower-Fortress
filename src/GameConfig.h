#pragma once
#include <array>
#include <raylib.h>

// TILE AND WINDOW DIMENSIONS
constexpr int PURE_TILE_SIZE = 20;
constexpr int SCALE_FACTOR = 5;
constexpr int TILE_SIZE = PURE_TILE_SIZE * SCALE_FACTOR;

constexpr int WINDOW_TILE_WIDTH = 26;
constexpr int WINDOW_TILE_HEIGHT = 16;

constexpr int WINDOW_WIDTH = WINDOW_TILE_WIDTH * TILE_SIZE;
constexpr int WINDOW_HEIGHT = WINDOW_TILE_HEIGHT * TILE_SIZE;

// CUSTOM COLORS
constexpr Color BRIGHT_YELLOW = {255, 220, 0, 255};
constexpr Color DARK_CHARCOAL = {30, 30, 30, 255};
constexpr Color BRIGHT_CYAN = {0, 255, 255, 255}; 

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

constexpr Rectangle getTileSourceRect(int sheetIndex)
{
    return Rectangle{
        static_cast<float>((sheetIndex % TILE_SHEET_COLUMNS) * TILE_SPRITE_SIZE),
        static_cast<float>((sheetIndex / TILE_SHEET_COLUMNS) * TILE_SPRITE_SIZE),
        static_cast<float>(TILE_SPRITE_SIZE),
        static_cast<float>(TILE_SPRITE_SIZE)};
}

// TILE PROPERTY LOOKUP TABLE
// Array index = tile ID.
inline constexpr std::array<TileProperties, 72> TILE_PROPERTIES = {

    // Sheet row 1
    TileProperties{getTileSourceRect(17), true}, // tile ID 0
    TileProperties{getTileSourceRect(18), true}, // tile ID 1
    TileProperties{getTileSourceRect(19), true}, // tile ID 2
    TileProperties{getTileSourceRect(20), true}, // tile ID 3
    TileProperties{getTileSourceRect(21), true}, // tile ID 4
    TileProperties{getTileSourceRect(22), true}, // tile ID 5
    TileProperties{getTileSourceRect(23), true}, // tile ID 6

    // Sheet row 2
    TileProperties{getTileSourceRect(33), true},  // tile ID 7
    TileProperties{getTileSourceRect(34), false}, // tile ID 8 - empty
    TileProperties{getTileSourceRect(35), true},  // tile ID 9
    TileProperties{getTileSourceRect(36), true},  // tile ID 10
    TileProperties{getTileSourceRect(37), true},  // tile ID 11
    TileProperties{getTileSourceRect(38), false}, // tile ID 12 - spikes
    TileProperties{getTileSourceRect(39), true},  // tile ID 13

    // Sheet row 3
    TileProperties{getTileSourceRect(49), true}, // tile ID 14
    TileProperties{getTileSourceRect(50), true}, // tile ID 15
    TileProperties{getTileSourceRect(51), true}, // tile ID 16
    TileProperties{getTileSourceRect(52), true}, // tile ID 17
    TileProperties{getTileSourceRect(53), true}, // tile ID 18
    TileProperties{getTileSourceRect(54), true}, // tile ID 19
    TileProperties{getTileSourceRect(55), true}, // tile ID 20

    // Sheet row 4
    TileProperties{getTileSourceRect(65), true}, // tile ID 21
    TileProperties{getTileSourceRect(66), true}, // tile ID 22
    TileProperties{getTileSourceRect(67), true}, // tile ID 23
    TileProperties{getTileSourceRect(68), true}, // tile ID 24
    TileProperties{getTileSourceRect(69), true}, // tile ID 25
    TileProperties{getTileSourceRect(70), true}, // tile ID 26
    TileProperties{getTileSourceRect(71), true}, // tile ID 27

    // Sheet row 5
    TileProperties{getTileSourceRect(81), false}, // tile ID 28 - decor
    TileProperties{getTileSourceRect(82), false}, // tile ID 29 - decor
    TileProperties{getTileSourceRect(83), false}, // tile ID 30 - window
    TileProperties{getTileSourceRect(84), false}, // tile ID 31 - window
    TileProperties{getTileSourceRect(85), false}, // tile ID 32 - bg wall
    TileProperties{getTileSourceRect(86), false}, // tile ID 33 - bg wall
    TileProperties{getTileSourceRect(87), false}, // tile ID 34 - bg wall

    // Sheet row 6
    TileProperties{getTileSourceRect(97), false},  // tile ID 35 - chain
    TileProperties{getTileSourceRect(98), false},  // tile ID 36 - chain
    TileProperties{getTileSourceRect(99), false},  // tile ID 37 - window
    TileProperties{getTileSourceRect(100), false}, // tile ID 38 - window
    TileProperties{getTileSourceRect(101), false}, // tile ID 39 - bg wall
    TileProperties{getTileSourceRect(102), false}, // tile ID 40 - bg wall
    TileProperties{getTileSourceRect(103), false}, // tile ID 41 - bg wall

    // Sheet row 8
    TileProperties{getTileSourceRect(129), true}, // tile ID 42
    TileProperties{getTileSourceRect(130), true}, // tile ID 43
    TileProperties{getTileSourceRect(131), true}, // tile ID 44
    TileProperties{getTileSourceRect(132), true}, // tile ID 45
    TileProperties{getTileSourceRect(133), true}, // tile ID 46
    TileProperties{getTileSourceRect(134), true}, // tile ID 47
    TileProperties{getTileSourceRect(135), true}, // tile ID 48

    // Sheet row 9
    TileProperties{getTileSourceRect(145), true},  // tile ID 49
    TileProperties{getTileSourceRect(146), false}, // tile ID 50 - empty/black
    TileProperties{getTileSourceRect(147), true},  // tile ID 51
    TileProperties{getTileSourceRect(148), true},  // tile ID 52
    TileProperties{getTileSourceRect(149), true},  // tile ID 53
    TileProperties{getTileSourceRect(151), true},  // tile ID 54

    // Sheet row 10
    TileProperties{getTileSourceRect(161), true}, // tile ID 55
    TileProperties{getTileSourceRect(162), true}, // tile ID 56
    TileProperties{getTileSourceRect(163), true}, // tile ID 57
    TileProperties{getTileSourceRect(164), true}, // tile ID 58
    TileProperties{getTileSourceRect(165), true}, // tile ID 59
    TileProperties{getTileSourceRect(166), true}, // tile ID 60
    TileProperties{getTileSourceRect(167), true}, // tile ID 61

    // Sheet row 11
    TileProperties{getTileSourceRect(177), true},  // tile ID 62
    TileProperties{getTileSourceRect(178), true},  // tile ID 63
    TileProperties{getTileSourceRect(179), true},  // tile ID 64
    TileProperties{getTileSourceRect(180), true},  // tile ID 65
    TileProperties{getTileSourceRect(181), false}, // tile ID 66 - decor

    // Sheet row 12
    TileProperties{getTileSourceRect(193), false}, // tile ID 67 - decor
    TileProperties{getTileSourceRect(194), false}, // tile ID 68 - decor
    TileProperties{getTileSourceRect(195), false}, // tile ID 69 - decor
    TileProperties{getTileSourceRect(196), false}, // tile ID 70 - decor
    TileProperties{getTileSourceRect(197), false}  // tile ID 71 - decor
};