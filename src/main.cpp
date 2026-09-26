#include <raylib.h>

#include "GameConfig.h"
#include "player/Player.h"
#include "world/Map.h"
#include "world/Tile.h"

float resolveCameraX(float playerX, float offsetX, int mapWidth)
{
    if (playerX - offsetX < 0)
    {
        return offsetX;
    }
    else if (playerX + offsetX > mapWidth * TILE_SIZE)
    {
        return mapWidth * TILE_SIZE - offsetX;
    }
    else
    {
        return playerX;
    }
}

float resolveCameraY(float playerY, float offsetY, int mapHeight)
{
    if (playerY - offsetY < 0)
    {
        return offsetY;
    }
    else if (playerY + offsetY > mapHeight * TILE_SIZE)
    {
        return mapHeight * TILE_SIZE - offsetY;
    }
    else
    {
        return playerY;
    }
}

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tower Fortress");
    SetTargetFPS(60);

    Map map;
    map.Load("assets/mapdata.txt", 64, 23); // 64 - wide, 23 - tall

    Player player(100, 100, 80, 80, BRIGHTYELLOW);

    // leaving camera stuff in here for now

    Camera2D camera{};

    camera.offset = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f}; // 900, 600
    camera.target = {player.getCenter()};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Vector2 deadZoneOffset = {camera.offset.x / 2.0f, camera.offset.y/ 2.0f}; // 450, 300

    // end of camera stuff

    while (!WindowShouldClose())
    {
        // updating
        player.Update(map);

        camera.target = Vector2{
            resolveCameraX(player.getCenter().x, camera.offset.x, map.getWidth()),
            resolveCameraY(player.getCenter().y, camera.offset.y, map.getHeight())};

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