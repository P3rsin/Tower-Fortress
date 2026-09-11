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

    Player player(100, 100, BRIGHTYELLOW);

    while (!WindowShouldClose())
    {
        // updating
        player.Update(map);

        // drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        map.Draw();
        player.Draw();
        player.DrawDebug();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}