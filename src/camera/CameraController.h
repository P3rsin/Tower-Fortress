#pragma once
#include <raylib.h>
#include "GameConfig.h"

class CameraController
{
public:
    CameraController(Vector2 target);

    void setZoom(float zoom);

    void entityFocus(Vector2 playerCenter, int mapWidth, int mapHeight);
    void freeMove();

    Camera2D &getCamera();

private:
    Camera2D camera;

    float clampCameraX(float playerX, float halfViewWidth, int mapWidth);
    float clampCameraY(float playerY, float halfViewHeight, int mapHeight);
};