#include <iostream>
#include <fstream>
#include <algorithm>
#include <raylib.h>

#include "GameConfig.h"
#include "world/Map.h"
#include "world/Tile.h"

Map::Map(const std::string &filePath)
{
    load(filePath);
}

Map::~Map()
{
    UnloadTexture(tileSheet);
}

void Map::loadMapIDs()
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

void Map::createTiles()
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

void Map::load(const std::string &filePath)
{
    tileSheet = LoadTexture("assets/desert-ruins.png");
    this->filePath = filePath;

    loadMapIDs();

    totalTiles = width * height;

    createTiles();
}

void Map::draw(const Camera2D &camera) const
{
    float halfViewWidth = camera.offset.x / camera.zoom;
    float halfViewHeight = camera.offset.y / camera.zoom;

    int startX = (camera.target.x - halfViewWidth) / TILE_SIZE;
    int endX = (camera.target.x + halfViewWidth) / TILE_SIZE;

    int startY = (camera.target.y - halfViewHeight) / TILE_SIZE;
    int endY = (camera.target.y + halfViewHeight) / TILE_SIZE;

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
        }
    }
}

const Tile &Map::getTile(TileCoord coordinate) const
{
    return tileList[(coordinate.y * width) + coordinate.x];
}

const std::vector<Tile> &Map::getTileList() const
{
    return tileList;
}

void Map::setTileID(int tileX, int tileY, int id)
{
    tileList[(tileY * width) + tileX].setID(id);
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

const Texture2D &Map::getTileSheet() const
{
    return tileSheet;
}