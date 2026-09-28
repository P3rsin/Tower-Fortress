#pragma once
#include "world/Tile.h"
#include "world/Map.h"

class MapEditor
{
public:
    MapEditor(const Texture2D &tileSheet);

    void highlightTiles(TileCoord start, TileCoord end) const;
    void drawDebug(const Tile &tile) const;

    void update(const Camera2D &camera);
    void save(const Map &map);
    void drawUI();

private:
    Texture2D tileSheet;

    TileCoord selectedTile = {-1, -1};
};
