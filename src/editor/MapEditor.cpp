#include <fstream>
#include <algorithm>
#include <cmath>

#include "MapEditor.h"
#include "world/Map.h"
#include "GameConfig.h"

MapEditor::MapEditor(Map &map)
    : map(map)
{
}

void MapEditor::clampCoordinate(TileCoord &coordinate) const
{
    coordinate.x = std::clamp(coordinate.x, 0, map.getWidth() - 1);
    coordinate.y = std::clamp(coordinate.y, 0, map.getHeight() - 1);
}

void MapEditor::highlightTiles() const
{
    const int xStart = std::min(selection->start.x, selection->end.x);
    const int xEnd = std::max(selection->start.x, selection->end.x);

    const int yStart = std::min(selection->start.y, selection->end.y);
    const int yEnd = std::max(selection->start.y, selection->end.y);

    Rectangle selectionRect = {
        static_cast<float>(xStart * TILE_SIZE),
        static_cast<float>(yStart * TILE_SIZE),
        static_cast<float>((xEnd - xStart + 1) * TILE_SIZE),
        static_cast<float>((yEnd - yStart + 1) * TILE_SIZE)};

    DrawRectangleLinesEx(selectionRect, 4.0f, BRIGHT_CYAN);

    for (int y = yStart; y <= yEnd; ++y)
    {
        for (int x = xStart; x <= xEnd; ++x)
        {
            const Tile &tile = map.getTile(TileCoord{x, y});
            DrawRectangleLinesEx(tile.getBody(), 1.0f, BRIGHT_CYAN);
        }
    }
}

void MapEditor::drawPalette() const
{
    int pbdHeightTiles = TILE_PROPERTIES.size() / WINDOW_TILE_WIDTH;

    if (TILE_PROPERTIES.size() % WINDOW_TILE_WIDTH != 0)
    {
        pbdHeightTiles++;
    }

    int pbdY = WINDOW_HEIGHT - (pbdHeightTiles * TILE_SIZE);

    Rectangle paletteBackDrop = {
        0.0f,
        static_cast<float>(pbdY) - BORDER_SIZE * 2,
        static_cast<float>(WINDOW_WIDTH),
        static_cast<float>(pbdHeightTiles * TILE_SIZE) + BORDER_SIZE * 2};

    DrawRectangleRec(paletteBackDrop, DARK_CHARCOAL);

    for (int i = 0; i < TILE_PROPERTIES.size(); i++)
    {
        Rectangle source = TILE_PROPERTIES[i].sourceRect;

        int rowCounter = i / WINDOW_TILE_WIDTH;

        constexpr float TILE_PADDING = 2.0f;

        float x =
            BORDER_SIZE +
            (i % WINDOW_TILE_WIDTH) * TILE_SIZE +
            TILE_PADDING;

        float y =
            paletteBackDrop.y +
            BORDER_SIZE +
            (rowCounter * TILE_SIZE) +
            TILE_PADDING;

        Rectangle destination = {
            x,
            y,
            TILE_SIZE - TILE_PADDING * 2,
            TILE_SIZE - TILE_PADDING * 2};

        DrawTexturePro(
            map.getTileSheet(),
            source,
            destination,
            {0.0f, 0.0f},
            0.0f,
            WHITE);
    }

    DrawRectangleLinesEx(paletteBackDrop, 4.0f, WHITE);
}

void MapEditor::update(const Camera2D &camera)
{
    Vector2 mouseScreen = GetMousePosition();
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

void MapEditor::save() const
{
    std::ofstream file("assets/savedMap.txt");

    int rowCount = 0;

    for (const Tile &tile : map.getTileList())
    {
        if (tile.getID() < 10)
        {
            file << '0' << tile.getID() << ' ';
        }
        else
        {
            file << tile.getID() << ' ';
        }

        rowCount++;

        if (rowCount == map.getWidth())
        {
            file << '\n';
            rowCount = 0;
        }
    }

    file.close();
}