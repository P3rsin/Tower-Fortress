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
    map.Load("assets/mapdata.txt", 64, 23); // 64 - wide, 23 - tall

    Player player(100, 100, 80, 80, BRIGHTYELLOW);

    // leaving camera stuff in here for now

    Camera2D camera{};

    camera.offset = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
    camera.target = {player.getCenter()};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // end of camera stuff

    while (!WindowShouldClose())
    {
        // updating
        player.Update(map);

        camera.target = player.getCenter();

        // drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // World
        BeginMode2D(camera);

        map.Draw();
        player.Draw();

        EndMode2D();

        // UI stuff
        // player.DrawDebug();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}