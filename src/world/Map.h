#pragma once
#include <string>
#include <vector>

#include "world/Tile.h"

class Map
{
private:
    std::string filePath;
    std::string tileIDData;
    std::vector<Tile> tileList;

    void LoadMapIDs();
    void CreateTiles();

    void DrawDebug(const Tile &tile) const;

public:
    void Load(const std::string &filePath);
    void Draw() const;
    const Tile &getTile(int tileX, int tileY) const;
};