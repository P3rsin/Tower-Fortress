#pragma once

constexpr int PURE_TILE_SIZE = 20;
constexpr int SCALE_FACTOR = 5;
constexpr int TILE_SIZE = PURE_TILE_SIZE * SCALE_FACTOR;

constexpr int WINDOW_TILE_WIDTH = 18;
constexpr int WINDOW_TILE_HEIGHT = 12;

constexpr int WINDOW_WIDTH = WINDOW_TILE_WIDTH * TILE_SIZE;
constexpr int WINDOW_HEIGHT = WINDOW_TILE_HEIGHT * TILE_SIZE;