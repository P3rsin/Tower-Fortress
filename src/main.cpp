#include <raylib.h>
#include <algorithm>

#include "GameConfig.h"
#include "player/Player.h"
#include "world/Map.h"
#include "world/Tile.h"
#include <stdexcept>

enum class EditorMode
{
    Normal,
    Insert
};

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
    float moveSpeed = 10 / camera.zoom;

    if (IsKeyDown(KEY_A))
    {
        camera.target.x -= moveSpeed;
    }
    else if (IsKeyDown(KEY_D))
    {
        camera.target.x += moveSpeed;
    }

    if (IsKeyDown(KEY_W))
    {
        camera.target.y -= moveSpeed;
    }
    else if (IsKeyDown(KEY_S))
    {
        camera.target.y += moveSpeed;
    }

    if (IsKeyDown(KEY_Q))
    {
        camera.zoom -= 0.02f;
    }
    else if (IsKeyDown(KEY_E))
    {
        camera.zoom += 0.02f;
    }

    camera.zoom = std::clamp(camera.zoom, 0.4f, 2.0f);
}

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tower Fortress");
    SetTargetFPS(60);

    std::string gameMode = "playerMode";
    std::string typedText;
    TileCoord selectedTile = {0, 0};
    EditorMode editorMode = EditorMode::Normal;

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
            map.highlightTile(selectedTile.x, selectedTile.y, false);
            camera.zoom = 1.0f; // reset any highlight and zoom

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
            if (IsKeyPressed(KEY_I))
            {
                editorMode = EditorMode::Insert;
            }
            else if (IsKeyPressed(KEY_ENTER))
            {
                try
                {
                    int inputID = std::stoi(typedText);
                    map.setTileID(selectedTile.x, selectedTile.y, inputID);
                }
                catch (const std::invalid_argument &)
                {
                    // typedText was not a valid number
                }
                catch (const std::out_of_range &)
                {
                    // number was too large/small for int
                }

                typedText.clear();
                editorMode = EditorMode::Normal;
            }

            if (editorMode == EditorMode::Normal)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    // reset previous highlight
                    map.highlightTile(selectedTile.x, selectedTile.y, false);

                    Vector2 mouseScreen = GetMousePosition();
                    Vector2 mousePosition = GetScreenToWorld2D(mouseScreen, camera);

                    int tileX = mousePosition.x / TILE_SIZE;
                    int tileY = mousePosition.y / TILE_SIZE;

                    selectedTile = {tileX, tileY};

                    map.highlightTile(selectedTile.x, selectedTile.y, true);
                }

                editorCameraUpdate(camera);

                if (IsKeyPressed(KEY_P))
                {
                    map.Save();
                }
            }
            else if (editorMode == EditorMode::Insert)
            {
                int key = GetCharPressed();

                while (key > 0)
                {
                    typedText += static_cast<char>(key);
                    key = GetCharPressed();
                }

                if (IsKeyPressed(KEY_BACKSPACE) && !typedText.empty())
                {
                    typedText.pop_back();
                }
            }
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
        DrawText(TextFormat("[%d:%d]", selectedTile.x, selectedTile.y), 20, 50, 28, WHITE);
        DrawText(typedText.c_str(), 20, 80, 28, WHITE);

        EndDrawing();
    }

    map.Unload();
    CloseWindow();

    return 0;
}