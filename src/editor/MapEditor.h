#pragma once
#include <optional>

#include "world/Tile.h"
#include "world/Map.h"

struct TileSelection
{
    TileCoord start;
    TileCoord end;
};

class MapEditor
{
public:
    MapEditor(const Map &map);

    void drawPalette();
    void update(const Camera2D &camera);
    void save(const Map &map);
    void draw(const Map &map);
    void drawUI();

private:
    Texture2D tileSheet;

    int mapWidth;
    int mapHeight;

    std::optional<TileSelection> selection;

    void clampCoordinate(TileCoord &coordinate);
    void highlightTiles(const Map &map) const;
};
