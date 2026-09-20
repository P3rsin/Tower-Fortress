#pragma once
#include <string>
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

    const float maxXSpeed = 500.0f;
    const float maxYSpeed = 500.0f;

    const float xAccel = 2500.0f;
    const float yAccel = 2500.0f;

    const float xDeaccel = 3500.0f;
    const float yDeaccel = 3500.0f;

    bool xColliding = false;
    bool yColliding = false;

    void UpdateVelocity(float dt);
    void ResolveXCollision(const Map &map, float dt);
    void ResolveYCollision(const Map &map, float dt);

    std::vector<std::string> collisionDebug;
};