#pragma once

#include <string>
#include <vector>
#include "Tile.h"

class Map
{
private:
    std::vector<std::string> mapData;
    std::vector<Tile> tileList;
    std::string filePath;

    void ReadFileData();
    void CreateTiles();

public:
    void Load(std::string filePath);
    void Draw();
};