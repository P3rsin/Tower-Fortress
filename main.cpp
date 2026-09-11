#include <raylib.h>

#include "Player.h"
#include "Tile.h"
#include "Map.h"
#include "GameConfig.h"

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tower Fortress");
    SetTargetFPS(60);

    Map map;
    map.Load("GameData/mapdata.txt");

    for (Tile tile : map.getTileList()) {
        tile.setColor(BLACK);
    }

    Player player(0, 0, RED);

    while (!WindowShouldClose())
    {
        // updating
        player.Update(map.getTileList());

        // drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        map.Draw();
        player.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}