#include <raylib.h>
#include <algorithm>
#include <stdexcept>

#include "GameConfig.h"
#include "GameState.h"
#include "player/Player.h"
#include "world/Map.h"
#include "world/Tile.h"
#include "camera/CameraController.h"
#include "editor/MapEditor.h"

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tower Fortress");
    SetTargetFPS(60);

    GameState gameState = GameState::PlayerFocused;
    Texture2D tileSheet = LoadTexture("assets/desert-ruins.png");

    Map map("assets/map-one.txt", tileSheet);
    MapEditor mapEditor(tileSheet);
    Player player(100, 100, 80, 80, BRIGHTYELLOW);
    CameraController cameraC(player.getCenter());

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_Y) && gameState == GameState::PlayerFocused)
        {
            gameState = GameState::MapEditor;
        }
        else if (IsKeyPressed(KEY_Y) && gameState == GameState::MapEditor)
        {
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
            mapEditor.update(cameraC.getCamera());
            cameraC.freeMove();
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
            mapEditor.drawUI();
        }

        EndDrawing();
    }

    map.Unload();
    CloseWindow();

    return 0;
}