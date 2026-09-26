#include <fstream>
#include <iostream>
#include <algorithm>
#include <raylib.h>

#include "GameConfig.h"
#include "world/Map.h"
#include "world/Tile.h"

void Map::Unload()
{
    UnloadTexture(tileSheet);
}

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
    tileSheet = LoadTexture("assets/desert-ruins.png");
    this->filePath = filePath;

    LoadMapIDs();

    totalTiles = width * height;

    CreateTiles();
}

void Map::DrawDebug(const Tile &tile) const
{
    DrawRectangleLinesEx(tile.getBody(), 1.0f, PURPLE);
}

void Map::Draw(const Camera2D &camera) const
{
    int startX = (camera.target.x - camera.offset.x) / TILE_SIZE;
    int endX = (camera.target.x + camera.offset.x) / TILE_SIZE;

    int startY = (camera.target.y - camera.offset.y) / TILE_SIZE;
    int endY = (camera.target.y + camera.offset.y) / TILE_SIZE;

    startX = std::max(0, startX);
    startY = std::max(0, startY);

    endX = std::min(width - 1, endX);
    endY = std::min(height - 1, endY);

    for (int j = startY; j <= endY; j++)
    {
        for (int i = startX; i <= endX; i++)
        {
            const Tile &tile = tileList[(j * width) + i];

            Rectangle source = TILE_PROPERTIES[tile.getID()].sourceRect;
            Rectangle destination = tile.getBody();

            DrawTexturePro(
                tileSheet,
                source,
                destination,
                {0.0f, 0.0f},
                0.0f,
                WHITE);

            // DrawDebug(tile);
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