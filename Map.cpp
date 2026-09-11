#include <fstream>
#include <iostream>
#include <raylib.h>

#include "Map.h"
#include "Tile.h"
#include "GameConfig.h"

void Map::ReadFileData()
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cout << "error opening " << filePath << std::endl;
    }

    std::string line;

    while (getline(file, line))
    {
        mapData.push_back(line);
    }

    file.close();
}

void Map::CreateTiles()
{
    for (int i = 0; i < WINDOW_TILE_WIDTH; i++)
    {
        for (int j = 0; j < WINDOW_TILE_HEIGHT; j++)
        {
            std::string curTileID = mapData[j].substr(i * 3, 2);

            Rectangle rect = {
                static_cast<float>(i * TILE_SIZE),
                static_cast<float>(j * TILE_SIZE),
                static_cast<float>(TILE_SIZE),
                static_cast<float>(TILE_SIZE)};

            Tile tile = Tile(std::stoi(curTileID), rect);
            tileList.push_back(tile);
        }
    }
}

void Map::Load(std::string filePath)
{
    this->filePath = filePath;
    ReadFileData();
    CreateTiles();
}

void Map::Draw()
{
    for (Tile tile : tileList)
    {
        DrawRectangleRec(tile.getBody(), tile.getColor());
    }
}

const std::vector<Tile> &Map::getTileList() const
{
    return tileList;
}