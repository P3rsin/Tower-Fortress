#pragma once
#include <vector>
#include <raylib.h>

constexpr int PURE_TILE_SIZE = 20;
constexpr int SCALE_FACTOR = 5;
constexpr int TILE_SIZE = PURE_TILE_SIZE * SCALE_FACTOR;

constexpr int WINDOW_TILE_WIDTH = 18;
constexpr int WINDOW_TILE_HEIGHT = 12;
constexpr int TOTAL_NUM_TILES = WINDOW_TILE_WIDTH * WINDOW_TILE_HEIGHT;

constexpr int WINDOW_WIDTH = WINDOW_TILE_WIDTH * TILE_SIZE;
constexpr int WINDOW_HEIGHT = WINDOW_TILE_HEIGHT * TILE_SIZE;

inline const std::vector<Color> TILE_COLORS = {PURPLE, BLUE};
inline const std::vector<int> TILE_COLLISIONS = {1, 0};