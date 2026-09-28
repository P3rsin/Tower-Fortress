#include <fstream>

#include "MapEditor.h"
#include "world/Map.h"
#include "GameConfig.h"

MapEditor::MapEditor(const Texture2D &tileSheet)
{
    this->tileSheet = tileSheet;
}

void MapEditor::drawDebug(const Tile &tile) const
{
    DrawRectangleLinesEx(tile.getBody(), 1.0f, RED);
}

void MapEditor::highlightTiles(TileCoord start, TileCoord end) const
{
    // first make a bold highlight around the box
    // then for tile in 2d range, highlight the tile lightly
}

void MapEditor::update(const Camera2D &camera) // looking out for input
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mouseScreen = GetMousePosition();
        Vector2 mousePosition = GetScreenToWorld2D(mouseScreen, camera);

        int tileX = mousePosition.x / TILE_SIZE;
        int tileY = mousePosition.y / TILE_SIZE;

        selectedTile = {tileX, tileY};
    }
}

void MapEditor::drawUI()
{
    DrawText(TextFormat("[%d:%d]", selectedTile.x, selectedTile.y), 20, 50, 28, WHITE);

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