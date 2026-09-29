#include <fstream>
#include <algorithm>
#include <cmath>

#include "MapEditor.h"
#include "world/Map.h"
#include "GameConfig.h"

MapEditor::MapEditor(const Map &map)
{
    this->tileSheet = map.getTileSheet();
    this->mapWidth = map.getWidth();
    this->mapHeight = map.getHeight();
}

void MapEditor::clampCoordinate(TileCoord &coordinate)
{
    coordinate.x = std::clamp(coordinate.x, 0, mapWidth - 1);
    coordinate.y = std::clamp(coordinate.y, 0, mapWidth - 1);
}

void MapEditor::highlightTiles(const Map &map) const
{
    const int xStart = std::min(selection->start.x, selection->end.x);
    const int xEnd = std::max(selection->start.x, selection->end.x);

    const int yStart = std::min(selection->start.y, selection->end.y);
    const int yEnd = std::max(selection->start.y, selection->end.y);

    Rectangle totalHighlight = {
        xStart * TILE_SIZE,
        yStart * TILE_SIZE,
        (xEnd - xStart + 1) * TILE_SIZE,
        (yEnd - yStart + 1) * TILE_SIZE};

    DrawRectangleLinesEx(totalHighlight, 4.0f, BRIGHT_CYAN);

    for (int y = yStart; y <= yEnd; ++y)
    {
        for (int x = xStart; x <= xEnd; ++x)
        {
            const Tile &tile = map.getTile(TileCoord{x, y});
            DrawRectangleLinesEx(tile.getBody(), 1.0f, BRIGHT_CYAN);
        }
    }
}

void MapEditor::drawPalette()
{
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

void MapEditor::draw(const Map &map)
{
    if (selection)
    {
        highlightTiles(map);
    }
}

void MapEditor::drawUI()
{
    if (selection)
    {
        DrawText(TextFormat("Tile 1: [%d:%d]", selection->start.x, selection->start.y), 20, 50, 28, WHITE);
        DrawText(TextFormat("Tile 2: [%d:%d]", selection->end.x, selection->end.y), 20, 85, 28, WHITE);
    }

    DrawTexturePro(
        tileSheet,
        TILE_PROPERTIES[0].sourceRect,
        Rectangle{0, 200, TILE_SIZE, TILE_SIZE},
        {0.0f, 0.0f},
        0.0f,
        WHITE);
}

void MapEditor::save(const Map &map)
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