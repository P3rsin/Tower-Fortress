#include <raylib.h>

#include "GameConfig.h"
#include "GameState.h"
#include "player/Player.h"
#include "world/Map.h"
#include "camera/CameraController.h"
#include "editor/MapEditor.h"

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tower Fortress");
    SetTargetFPS(60);

    GameState gameState = GameState::PlayerFocused;

    Map map("assets/map-one.txt");
    MapEditor mapEditor(map);
    Player player(100, 100, 80, 80, BRIGHT_YELLOW);
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
            player.update(map);
            cameraC.entityFocus(player.getCenter(), map.getWidth(), map.getHeight());
        }
        else if (gameState == GameState::MapEditor)
        {
            mapEditor.update(cameraC.getCamera());
            cameraC.freeMove();
        }

        // drawing
        BeginDrawing();
        ClearBackground(DARK_CHARCOAL);

        // World
        BeginMode2D(cameraC.getCamera());

        map.draw(cameraC.getCamera());

        if (gameState == GameState::MapEditor)
        {
            mapEditor.draw(map);
        }

        player.draw();

        EndMode2D();

        // UI stuff
        if (gameState == GameState::MapEditor)
        {
            mapEditor.drawUI();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}