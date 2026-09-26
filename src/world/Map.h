#pragma once
#include <string>
#include <vector>

#include "world/Tile.h"

class Map
{
public:
    void Load(const std::string &filePath);
    void Draw(int startX, int endX, int startY, int endY) const;
    const Tile &getTile(int tileX, int tileY) const;
    // bool isInBounds(int tileX, int tileY) const;

    int getWidth() const;
    int getHeight() const;

private:
    std::string filePath;
    std::string tileIDData;
    std::vector<Tile> tileList;

    int width;
    int height;
    int totalTiles;

    void LoadMapIDs();
    void CreateTiles();

    void DrawDebug(const Tile &tile) const;
};