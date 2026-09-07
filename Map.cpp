#include "Map.h"
#include "GameConfig.h"

#include <raylib.h>
#include <fstream>
#include <iostream>

void Map::Load(std::string filePath)
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

void Map::Draw()
{
    for (int i = 0; i < WINDOW_TILE_WIDTH; i++)
    {
        for (int j = 0; j < WINDOW_TILE_HEIGHT; j++)
        {
            std::string mapDataValue = mapData[j].substr(i * 3, 2);

            Color tileColor;

            if (mapDataValue == "01")
            {
                tileColor = BLUE;
            }
            else
            {
                tileColor = PURPLE;
            }

            DrawRectangle(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, tileColor);
        }
    }
}
