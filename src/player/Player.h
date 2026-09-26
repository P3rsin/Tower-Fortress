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
    Rectangle getBody() const;
    Vector2 getCenter() const;

private:
    Rectangle body;
    Color color;

    float xVelocity = 0.0f;
    const float maxXSpeed = 650.0f;
    const float xAccel = 7000.0f;
    const float airAccel = 3000.0f;
    const float xDeaccel = 7000.0f;
    const float airDeaccel = 1200.0f;

    float yVelocity = 0.0f;
    const float maxFallSpeed = 1500.0f;
    const float gravity = 3000.0f;
    const float jumpSpeed = 1150.0f;

    bool isGrounded = false;
    bool hitCeiling = false;
    bool sustainingJump = false;

    float coyoteTimer = 0.0f;
    float jumpBufferTimer = 0.0f;
    float releasedJumpEarlyScale = 2.5f;

    void UpdateVelocity(float dt);
    void ResolveXCollision(const Map &map, float dt);
    void ResolveYCollision(const Map &map, float dt);

    std::vector<std::string> collisionDebug;
};