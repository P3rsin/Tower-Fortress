#pragma once
#include <string>
#include <vector>

#include "Tile.h"

class Map
{
private:
    std::string filePath;
    std::vector<std::string> mapData;
    std::vector<Tile> tileList;

    void ReadFileData();
    void CreateTiles();

public:
    void Load(std::string filePath);
    void Draw();
    const std::vector<Tile> &getTileList() const;
};