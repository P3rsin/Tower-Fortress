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
    explicit MapEditor(Map &map);

    void drawPalette() const;
    void update(const Camera2D &camera);
    void save() const;
    void draw() const;
    void drawUI() const;

private:
    Map &map;
    std::optional<TileSelection> selection;

    void clampCoordinate(TileCoord &coordinate) const;
    void highlightTiles() const;
};