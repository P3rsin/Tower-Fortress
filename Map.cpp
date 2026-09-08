#include "Map.h"
#include "Tile.h"
#include "GameConfig.h"

#include <raylib.h>
#include <fstream>
#include <iostream>

void Map::ReadFileData()
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cout << "Map Data file opening error!";
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
            Rectangle rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};

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
    for (int i = 0; i < TOTAL_NUM_TILES; i++)
    {
        Color tileColor;

        if (tileList[i].getID() == 1)
        {
            tileColor = BLUE;
        }
        else
        {
            tileColor = PURPLE;
        }

        DrawRectangleRec(tileList[i].getBody(), tileColor);
    }
}
