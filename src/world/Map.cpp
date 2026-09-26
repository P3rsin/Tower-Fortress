#include <fstream>
#include <iostream>
#include <raylib.h>

#include "GameConfig.h"
#include "world/Map.h"
#include "world/Tile.h"
#include "debug/Debug.h"

void Map::LoadMapIDs()
{
    width = 0;
    height = 0;

    tileIDData.clear();
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "error opening " << filePath << '\n';
        return;
    }

    std::string line;

    while (getline(file, line))
    {
        if (width == 0)
        {
            width = line.size() / TILE_ID_STRIDE;
        }

        height++;
        tileIDData += line;
    }
}

void Map::CreateTiles()
{
    tileList.clear();

    for (size_t i = 0; i < totalTiles; i++)
    {
        const int tileX = i % width;
        const int tileY = i / width;

        const size_t retrievalIdx = i * TILE_ID_STRIDE;
        const std::string curTileID = tileIDData.substr(retrievalIdx, TILE_ID_LENGTH);

        const Rectangle rect = {
            static_cast<float>(tileX * TILE_SIZE),
            static_cast<float>(tileY * TILE_SIZE),
            static_cast<float>(TILE_SIZE),
            static_cast<float>(TILE_SIZE)};

        tileList.emplace_back(std::stoi(curTileID), rect);
    }
}

void Map::Load(const std::string &filePath)
{
    this->filePath = filePath;

    LoadMapIDs();

    totalTiles = width * height;

    CreateTiles();
}

void Map::DrawDebug(const Tile &tile) const
{
    DrawRectangleLinesEx(tile.getBody(), 1.0f, PURPLE);
}

void Map::Draw(int startX, int endX, int startY, int endY) const
{
    for (int i = startX; i <= endX; i++)
    {
        for (int j = startY; j <= endY; j++)
        {
            const Tile &tile = tileList[(j * width) + i];
            DrawRectangleRec(tile.getBody(), tile.getColor());
            DrawDebug(tile);
        }
    }
}

const Tile &Map::getTile(int tileX, int tileY) const
{
    return tileList[(tileY * width) + tileX];
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

// unused
// bool Map::isInBounds(int tileX, int tileY) const
// {
//     return tileX >= 0 && tileX < width && tileY >= 0 && tileY < height;
// }