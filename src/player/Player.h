#pragma once
#include <string>
#include <vector>
#include <raylib.h>

#include "world/Map.h"

class Player
{
public:
    Player(float startX, float startY, float width, float height, Color color);

    void Update(const Map &map);
    void Draw() const;
    void DrawDebug() const;

private:
    Rectangle body;
    Color color;

    float xVelocity = 0.0f;
    const float maxXSpeed = 650.0f;
    const float xAccel = 6250.0f;
    const float airAccel = 3000.0f;
    const float xDeaccel = 9000.0f;

    float yVelocity = 0.0f;
    const float maxFallSpeed = 1200.0f;
    const float gravity = 2500.0f;
    const float jumpSpeed = 900.0f;

    bool xColliding = false;
    bool yColliding = false;

    bool isGrounded = false;
    bool hitCeiling = false;
    bool falling = false;

    void UpdateVelocity(float dt);
    void ResolveXCollision(const Map &map, float dt);
    void ResolveYCollision(const Map &map, float dt);

    std::vector<std::string> collisionDebug;
};