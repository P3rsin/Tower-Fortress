#pragma once
#include <string>
#include <vector>

#include "world/Tile.h"

class Map
{
public:
    Map(const std::string &filePath);
    ~Map();

    // avoid attempting to delete the same texture
    Map(const Map &) = delete;
    Map &operator=(const Map &) = delete;

    void load(const std::string &filePath);
    void draw(const Camera2D &camera) const;

    const Tile &getTile(TileCoord coordinate) const;
    const std::vector<Tile> &getTileList() const;

    void setTileID(int tileX, int tileY, int id);

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

    void loadMapIDs();
    void createTiles();
};