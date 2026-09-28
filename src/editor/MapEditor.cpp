#include <fstream>

#include "MapEditor.h"
#include "world/Map.h"
#include "GameConfig.h"

MapEditor::MapEditor(const Map &map)
{
    this->tileSheet = map.getTileSheet();
    this->mapWidth = map.getWidth();
    this->mapHeight = map.getHeight();
}

void MapEditor::drawDebug(const Tile &tile) const
{
    DrawRectangleLinesEx(tile.getBody(), 1.0f, RED);
}

void MapEditor::correctCoord(TileCoord &coordinate)
{
    if (coordinate.x < 0 || coordinate.x > mapWidth - 1)
    {
        if (std::abs(0 - coordinate.x) < std::abs(mapWidth - 1 - coordinate.x))
        {
            coordinate.x = 0;
        }
        else
        {
            coordinate.x = mapWidth - 1;
        }
    }

    if (coordinate.y < 0 || coordinate.y > mapHeight - 1)
    {
        if (std::abs(0 - coordinate.y) < std::abs(mapHeight - 1 - coordinate.y))
        {
            coordinate.y = 0;
        }
        else
        {
            coordinate.y = mapHeight - 1;
        }
    }
}

void MapEditor::highlightTiles(const Map &map) const
{
    int xStart;
    int yStart;

    int xEnd;
    int yEnd;

    const TileCoord &selectedTile = selection->start;
    const TileCoord &selectedTile2 = selection->end;

    if (selectedTile.x <= selectedTile2.x)
    {
        xStart = selectedTile.x;
        xEnd = selectedTile2.x;
    }
    else
    {
        xStart = selectedTile2.x;
        xEnd = selectedTile.x;
    }

    if (selectedTile.y <= selectedTile2.y)
    {
        yStart = selectedTile.y;
        yEnd = selectedTile2.y;
    }
    else
    {
        yStart = selectedTile2.y;
        yEnd = selectedTile.y;
    }

    Rectangle totalHighlight = {
        xStart * TILE_SIZE,
        yStart * TILE_SIZE,
        (xEnd - xStart + 1) * TILE_SIZE,
        (yEnd - yStart + 1) * TILE_SIZE};

    DrawRectangleLinesEx(totalHighlight, 4.0f, BRIGHTCYAN);

    for (int i = xStart; i <= xEnd; i++)
    {
        for (int j = yStart; j <= yEnd; j++)
        {
            const Tile &tile = map.getTile(TileCoord{i, j});
            DrawRectangleLinesEx(tile.getBody(), 1.0f, BRIGHTCYAN);
        }
    }
}

void MapEditor::drawPallete()
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
        correctCoord(coord);

        selection = TileSelection{coord, coord};
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        if (selection)
        {
            TileCoord coord{tileX, tileY};
            correctCoord(coord);

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