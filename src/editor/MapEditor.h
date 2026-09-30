#pragma once
#include <optional>
#include <vector>

#include "world/Tile.h"
#include "world/Map.h"

struct TileSelection
{
    TileCoord start;
    TileCoord end;
};

struct PaletteTile
{
    int tileID;
    Rectangle body;
};

struct SelectionBounds
{
    int xStart;
    int xEnd;
    int yStart;
    int yEnd;
};

class MapEditor
{
public:
    explicit MapEditor(Map &map);

    void setPalette();
    void drawPalette() const;
    void update(const Camera2D &camera);
    void save() const;
    void draw() const;
    void drawUI() const;

private:
    Map &map;
    std::optional<TileSelection> selection;

    Rectangle paletteBackDrop;
    std::vector<PaletteTile> paletteTiles;
    std::optional<int> selectedTileID;

    void applySelectedTile();

    void clampCoordinate(TileCoord &coordinate) const;
    void highlightTiles() const;
    SelectionBounds getSelectionBounds() const;
};