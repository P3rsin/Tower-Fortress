#include <fstream>
#include <iostream>
#include <raylib.h>

#include "Map.h"
#include "Tile.h"
#include "GameConfig.h"
#include "Debug.h"

void Map::LoadMapIDs()
{
    tileIDData = "";
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cout << "error opening " << filePath << std::endl;
    }

    std::string line;

    while (getline(file, line))
    {
        tileIDData += line;
    }

    file.close();
}

void Map::CreateTiles()
{
    for (int i = 0; i < TOTAL_NUM_TILES; i++)
    {
        int tileX = i % WINDOW_TILE_WIDTH;
        int tileY = i / WINDOW_TILE_WIDTH;

        int retrievalIdx = i * TILE_ID_STRIDE;
        std::string curTileID = tileIDData.substr(retrievalIdx, TILE_ID_LENGTH);

        Rectangle rect = {
            static_cast<float>(tileX * TILE_SIZE),
            static_cast<float>(tileY * TILE_SIZE),
            static_cast<float>(TILE_SIZE),
            static_cast<float>(TILE_SIZE)};

        Tile tile = Tile(std::stoi(curTileID), rect);
        tileList.push_back(tile);
    }
}

void Map::Load(std::string filePath)
{
    this->filePath = filePath;
    LoadMapIDs();
    CreateTiles();
}

void Map::DrawDebug(const Tile &tile)
{
    DrawRectangleLinesEx(
        tile.getBody(),
        1.0f,
        PURPLE);
}

void Map::Draw()
{
    for (const Tile &tile : tileList)
    {
        DrawRectangleRec(tile.getBody(), tile.getColor());
        DrawDebug(tile);
    }
}

const Tile &Map::getTile(int tileX, int tileY) const
{
    return tileList[(tileY * WINDOW_TILE_WIDTH) + tileX];
}