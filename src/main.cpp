#include <raylib.h>
#include <algorithm>
#include <stdexcept>

#include "GameConfig.h"
#include "GameState.h"
#include "player/Player.h"
#include "world/Map.h"
#include "world/Tile.h"
#include "camera/CameraController.h"

enum class EditorMode
{
    Normal,
    Insert
};

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tower Fortress");
    SetTargetFPS(60);

    GameState gameState = GameState::PlayerFocused;
    EditorMode editorMode = EditorMode::Normal;

    std::string typedText;
    TileCoord selectedTile = {0, 0};

    Texture2D tileSheet = LoadTexture("assets/desert-ruins.png");

    Map map("assets/map-one.txt", tileSheet);
    Player player(100, 100, 80, 80, BRIGHTYELLOW);
    CameraController cameraC(player.getCenter());

    while (!WindowShouldClose())
    {
        // set gamemode logic
        if (IsKeyPressed(KEY_Y) && gameState == GameState::PlayerFocused)
        {
            gameState = GameState::MapEditor;
        }
        else if (IsKeyPressed(KEY_Y) && gameState == GameState::MapEditor)
        {
            map.highlightTile(selectedTile.x, selectedTile.y, false);
            cameraC.setZoom(1.0f);

            gameState = GameState::PlayerFocused;
        }

        // update based on gamemode
        if (gameState == GameState::PlayerFocused)
        {
            player.Update(map);
            cameraC.entityFocus(player.getCenter(), map.getWidth(), map.getHeight());
        }
        else if (gameState == GameState::MapEditor)
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
                    Vector2 mousePosition = GetScreenToWorld2D(mouseScreen, cameraC.getCamera());

                    int tileX = mousePosition.x / TILE_SIZE;
                    int tileY = mousePosition.y / TILE_SIZE;

                    selectedTile = {tileX, tileY};

                    map.highlightTile(selectedTile.x, selectedTile.y, true);
                }

                cameraC.freeMove();

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
        BeginMode2D(cameraC.getCamera());

        map.Draw(cameraC.getCamera());
        player.Draw();

        EndMode2D();

        // UI stuff
        if (gameState == GameState::MapEditor)
        {
            DrawText(TextFormat("[%d:%d]", selectedTile.x, selectedTile.y), 20, 50, 28, WHITE);
            DrawText(typedText.c_str(), 20, 80, 28, WHITE);

            DrawTexturePro(
                tileSheet,
                TILE_PROPERTIES[0].sourceRect,
                Rectangle{0, 200, TILE_SIZE, TILE_SIZE},
                {0.0f, 0.0f},
                0.0f,
                WHITE);
        }

        EndDrawing();
    }

    map.Unload();
    CloseWindow();

    return 0;
}