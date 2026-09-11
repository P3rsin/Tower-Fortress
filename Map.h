#pragma once
#include <string>
#include <vector>

#include "Tile.h"

class Map
{
private:
    std::string filePath;
    std::string tileIDData;
    std::vector<Tile> tileList;

    void LoadMapIDs();
    void CreateTiles();

public:
    void Load(std::string filePath);
    void Draw();
    const Tile &getTile(int tileX, int tileY) const;
};