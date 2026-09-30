#include <fstream>
#include <algorithm>
#include <cmath>

#include "MapEditor.h"
#include "world/Map.h"
#include "GameConfig.h"

MapEditor::MapEditor(Map &map)
    : map(map)
{
    setPalette();
}

void MapEditor::clampCoordinate(TileCoord &coordinate) const
{
    coordinate.x = std::clamp(coordinate.x, 0, map.getWidth() - 1);
    coordinate.y = std::clamp(coordinate.y, 0, map.getHeight() - 1);
}

SelectionBounds MapEditor::getSelectionBounds() const
{
    return {
        std::min(selection->start.x, selection->end.x),
        std::max(selection->start.x, selection->end.x),
        std::min(selection->start.y, selection->end.y),
        std::max(selection->start.y, selection->end.y)};
}

void MapEditor::highlightTiles() const
{
    const SelectionBounds bounds = getSelectionBounds();

    Rectangle selectionRect = {
        static_cast<float>(bounds.xStart * TILE_SIZE),
        static_cast<float>(bounds.yStart * TILE_SIZE),
        static_cast<float>((bounds.xEnd - bounds.xStart + 1) * TILE_SIZE),
        static_cast<float>((bounds.yEnd - bounds.yStart + 1) * TILE_SIZE)};

    DrawRectangleLinesEx(selectionRect, 4.0f, BRIGHT_CYAN);

    for (int y = bounds.yStart; y <= bounds.yEnd; ++y)
    {
        for (int x = bounds.xStart; x <= bounds.xEnd; ++x)
        {
            const Tile &tile = map.getTile({x, y});
            DrawRectangleLinesEx(tile.getBody(), 1.0f, BRIGHT_CYAN);
        }
    }
}

void MapEditor::setPalette()
{
    int pbdHeightTiles = (TILE_PROPERTIES.size() + WINDOW_TILE_WIDTH - 1) / WINDOW_TILE_WIDTH;
    int pbdY = WINDOW_HEIGHT - (pbdHeightTiles * TILE_SIZE);

    paletteBackDrop = {
        0.0f,
        static_cast<float>(pbdY) - BORDER_SIZE * 2,
        static_cast<float>(WINDOW_WIDTH),
        static_cast<float>(pbdHeightTiles * TILE_SIZE) + BORDER_SIZE * 2};

    paletteTiles.clear();

    for (int i = 0; i < static_cast<int>(TILE_PROPERTIES.size()); ++i)
    {
        int row = i / WINDOW_TILE_WIDTH;
        int column = i % WINDOW_TILE_WIDTH;

        float x = BORDER_SIZE + column * TILE_SIZE + TILE_PADDING;
        float y = paletteBackDrop.y + BORDER_SIZE + row * TILE_SIZE + TILE_PADDING;

        Rectangle body = {
            x,
            y,
            TILE_SIZE - TILE_PADDING * 2,
            TILE_SIZE - TILE_PADDING * 2};

        paletteTiles.push_back({i, body});
    }
}

void MapEditor::drawPalette() const
{
    DrawRectangleRec(paletteBackDrop, DARK_CHARCOAL);

    for (const PaletteTile &paletteTile : paletteTiles)
    {
        Rectangle source = TILE_PROPERTIES[paletteTile.tileID].sourceRect;

        DrawTexturePro(
            map.getTileSheet(),
            source,
            paletteTile.body,
            {0.0f, 0.0f},
            0.0f,
            WHITE);

        if (selectedTileID && *selectedTileID == paletteTile.tileID)
        {
            DrawRectangleLinesEx(paletteTile.body, 3.0f, BRIGHT_CYAN);
        }
    }

    DrawRectangleLinesEx(paletteBackDrop, 4.0f, WHITE);
}

void MapEditor::applySelectedTile()
{
    if (!selectedTileID || !selection)
    {
        return;
    }

    const SelectionBounds bounds = getSelectionBounds();

    for (int y = bounds.yStart; y <= bounds.yEnd; ++y)
    {
        for (int x = bounds.xStart; x <= bounds.xEnd; ++x)
        {
            map.setTileID(x, y, *selectedTileID);
        }
    }
}

void MapEditor::update(const Camera2D &camera)
{
    Vector2 mouseScreen = GetMousePosition();

    if (CheckCollisionPointRec(mouseScreen, paletteBackDrop))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (const PaletteTile &paletteTile : paletteTiles)
            {
                if (CheckCollisionPointRec(mouseScreen, paletteTile.body))
                {
                    selectedTileID = paletteTile.tileID;
                    break;
                }
            }
        }
    }
    else
    {
        Vector2 mousePosition = GetScreenToWorld2D(mouseScreen, camera);
        int tileX = mousePosition.x / TILE_SIZE;
        int tileY = mousePosition.y / TILE_SIZE;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT))
        {
            TileCoord coord{tileX, tileY};
            clampCoordinate(coord);

            selection = TileSelection{coord, coord};
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_SHIFT))
        {
            if (selection)
            {
                TileCoord coord{tileX, tileY};
                clampCoordinate(coord);

                selection->end = coord;
            }
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        applySelectedTile();
    }
    else if (IsKeyPressed(KEY_P))
    {
        map.save();
    }
}

void MapEditor::draw() const
{
    if (selection)
    {
        highlightTiles();
    }
}

void MapEditor::drawUI() const
{
    if (selection)
    {
        DrawText(TextFormat("Tile 1: [%d:%d]", selection->start.x, selection->start.y), 20, 50, 28, WHITE);
        DrawText(TextFormat("Tile 2: [%d:%d]", selection->end.x, selection->end.y), 20, 85, 28, WHITE);
    }

    drawPalette();
}