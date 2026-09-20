#pragma once
#include <vector>
#include <raylib.h>

#include "world/Map.h"

class Player
{
public:
    Player(float startX, float startY, Color color);

    void Update(const Map &map);
    void Draw() const;
    void DrawDebug() const;

private:
    Rectangle body;
    Color color;

    float xVelocity = 0.0f;
    float yVelocity = 0.0f;

    float maxXSpeed = 10.0f;
    float maxYSpeed = 10.0f;

    float xAccel = 0.0f;
    float yAccel = 0.0f;

    float xDeaccel = 0.0f;
    float yDeaccel = 0.0f;

    bool xColliding = false;
    bool yColliding = false;

    void UpdateVelocity();
    void ResolveXCollision(const Map &map);
    void ResolveYCollision(const Map &map);

    std::vector<std::string> collisionDebug;
};