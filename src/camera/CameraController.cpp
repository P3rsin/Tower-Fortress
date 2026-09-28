#include <algorithm>

#include "CameraController.h"
#include "GameConfig.h"

CameraController::CameraController(Vector2 target)
{
    camera.offset = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
    camera.target = target;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

float CameraController::clampCameraX(float playerX, float halfViewWidth, int mapWidth)
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

float CameraController::clampCameraY(float playerY, float halfViewHeight, int mapHeight)
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

void CameraController::freeMove()
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

void CameraController::entityFocus(Vector2 target, int mapWidth, int mapHeight)
{
    float halfViewWidth = camera.offset.x / camera.zoom;
    float halfViewHeight = camera.offset.y / camera.zoom;

    camera.target = Vector2{
        clampCameraX(target.x, halfViewWidth, mapWidth),
        clampCameraY(target.y, halfViewHeight, mapHeight)};
}

void CameraController::setZoom(float zoom)
{
    camera.zoom = zoom;
}

Camera2D &CameraController::getCamera()
{
    return camera;
}