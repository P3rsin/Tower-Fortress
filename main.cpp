#include <raylib.h>

#include "Player.h"
#include "Map.h"
#include "GameConfig.h"

using namespace std;

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tower Fortress");
    SetTargetFPS(60);

    Player player(0, 0);
    Map map;

    map.Load("GameData/mapdata.txt");

    while (!WindowShouldClose())
    {
        // updating
        player.Update();

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