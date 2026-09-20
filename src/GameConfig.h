#pragma once
#include <array>
#include <raylib.h>

// TILE AND WINDOW DIMENSIONS
constexpr int PURE_TILE_SIZE = 20;
constexpr int SCALE_FACTOR = 5;
constexpr int TILE_SIZE = PURE_TILE_SIZE * SCALE_FACTOR;

constexpr int WINDOW_TILE_WIDTH = 18;
constexpr int WINDOW_TILE_HEIGHT = 12;
constexpr int TOTAL_NUM_TILES = WINDOW_TILE_WIDTH * WINDOW_TILE_HEIGHT;

constexpr int WINDOW_WIDTH = WINDOW_TILE_WIDTH * TILE_SIZE;
constexpr int WINDOW_HEIGHT = WINDOW_TILE_HEIGHT * TILE_SIZE;

// CUSTOM COLORS
constexpr Color DARKCHARCOAL = {25, 25, 30, 255};
constexpr Color BRIGHTYELLOW = {255, 220, 0, 255};
constexpr Color BRIGHTCYAN = {0, 200, 255, 255};

// TILE PROPERTY LOOKUP TABLES - arrays indexed by tile ID
struct TileProperties
{
    Color color;
    bool isSolid;
};

inline constexpr std::array<TileProperties, 2> TILE_PROPERTIES = {
    TileProperties{BRIGHTCYAN, true},
    TileProperties{DARKCHARCOAL, false}};

// MAP FILE PARSING - based on txt formatting used
constexpr std::size_t TILE_ID_LENGTH = 2;
constexpr std::size_t TILE_ID_SEPARATOR_LENGTH = 1;
constexpr std::size_t TILE_ID_STRIDE = TILE_ID_LENGTH + TILE_ID_SEPARATOR_LENGTH;