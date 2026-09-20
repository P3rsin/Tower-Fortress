#include <raylib.h>

#include "GameConfig.h"
#include "player/Player.h"
#include "world/Map.h"
#include "world/Tile.h"

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tower Fortress");
    SetTargetFPS(60);

    Map map;
    map.Load("assets/mapdata.txt");

    Player player(100, 100, 80, 80, BRIGHTYELLOW);

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