#pragma once
#include <string>
#include <vector>

#include "world/Tile.h"

class Map
{
public:
    Map(const std::string &filePath);

    void Load(const std::string &filePath);
    void Draw(const Camera2D &camera) const;

    const Tile &getTile(TileCoord coordinate) const;
    const std::vector<Tile> &getTileList() const;
    Tile &getTileRef(int tileX, int tileY);

    void setTileID(int tileX, int tileY, int id);
    void Unload();

    int getWidth() const;
    int getHeight() const;

    const Texture2D &getTileSheet() const;

private:
    std::string filePath;
    std::string tileIDData;
    std::vector<Tile> tileList;

    Texture2D tileSheet;

    int width;
    int height;
    int totalTiles;

    void LoadMapIDs();
    void CreateTiles();
};