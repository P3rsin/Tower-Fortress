#include <raylib.h>
#include <algorithm>

#include "GameConfig.h"
#include "player/Player.h"
#include "world/Map.h"
#include "world/Tile.h"

float clampCameraX(float playerX, float halfViewWidth, int mapWidth)
{
    if (playerX - halfViewWidth < 0)
    {
        return halfViewWidth;
    }
    else if (playerX + halfViewWidth > mapWidth * TILE_SIZE)
    {
        return mapWidth * TILE_SIZE - halfViewWidth;
    }
    else
    {
        return playerX;
    }
}

float clampCameraY(float playerY, float halfViewHeight, int mapHeight)
{
    if (playerY - halfViewHeight < 0)
    {
        return halfViewHeight;
    }
    else if (playerY + halfViewHeight > mapHeight * TILE_SIZE)
    {
        return mapHeight * TILE_SIZE - halfViewHeight;
    }
    else
    {
        return playerY;
    }
}

void editorCameraUpdate(Camera2D &camera)
{
    if (IsKeyDown(KEY_A))
    {
        camera.target.x -= 10;
    }
    else if (IsKeyDown(KEY_D))
    {
        camera.target.x += 10;
    }

    if (IsKeyDown(KEY_W))
    {
        camera.target.y -= 10;
    }
    else if (IsKeyDown(KEY_S))
    {
        camera.target.y += 10;
    }
}

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tower Fortress");
    SetTargetFPS(60);

    std::string gameMode = "playerMode";
    Vector2 selectedTileIdx = {0, 0};

    Map map;
    map.Load("assets/map-one.txt");

    Player player(100, 100, 80, 80, BRIGHTYELLOW);

    // leaving camera stuff in here for now
    Camera2D camera{};

    camera.offset = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f}; // 900, 600
    camera.target = player.getCenter();
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    // end of camera stuff

    while (!WindowShouldClose())
    {
        // set gamemode logic
        if (IsKeyPressed(KEY_Y) && gameMode == "playerMode")
        {
            gameMode = "editorMode";
        }
        else if (IsKeyPressed(KEY_Y) && gameMode == "editorMode")
        {
            // reset any highlight
            map.highlightTile(selectedTileIdx.x, selectedTileIdx.y, false);
            gameMode = "playerMode";
        }

        // update based on gamemode
        if (gameMode == "playerMode")
        {
            player.Update(map);

            // update the camera
            float halfViewWidth = camera.offset.x / camera.zoom;
            float halfViewHeight = camera.offset.y / camera.zoom;

            camera.target = Vector2{
                clampCameraX(player.getCenter().x, halfViewWidth, map.getWidth()),
                clampCameraY(player.getCenter().y, halfViewHeight, map.getHeight())};
        }
        else if (gameMode == "editorMode")
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // reset previous highlight
                map.highlightTile(selectedTileIdx.x, selectedTileIdx.y, false);

                Vector2 mouseScreen = GetMousePosition();
                Vector2 mousePosition = GetScreenToWorld2D(mouseScreen, camera);

                int tileX = mousePosition.x / TILE_SIZE;
                int tileY = mousePosition.y / TILE_SIZE;

                selectedTileIdx = {tileX, tileY};

                map.highlightTile(selectedTileIdx.x, selectedTileIdx.y, true);
            }

            editorCameraUpdate(camera);
        }

        // drawing
        BeginDrawing();
        ClearBackground(DARKCHARCOAL);

        // World
        BeginMode2D(camera);

        map.Draw(camera);
        player.Draw();

        EndMode2D();

        // UI stuff
        DrawText(gameMode.c_str(), 20, 20, 28, WHITE);
        DrawText(TextFormat("[%.0f:%.0f]", selectedTileIdx.x, selectedTileIdx.y),
                 20, 50, 28, WHITE);
        EndDrawing();
    }

    map.Unload();
    CloseWindow();

    return 0;
}