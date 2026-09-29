#pragma once
#include <raylib.h>

class CameraController
{
public:
    CameraController(Vector2 target);

    void setZoom(float zoom);

    void focusOn(Vector2 playerCenter, int mapWidth, int mapHeight);
    void freeMove();

    const Camera2D &getCamera() const;

private:
    Camera2D camera;

    float clampCameraX(float playerX, float halfViewWidth, int mapWidth);
    float clampCameraY(float playerY, float halfViewHeight, int mapHeight);
};