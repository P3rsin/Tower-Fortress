#include <vector>
#include <cmath>
#include <optional>
#include <raylib.h>

#include "Player.h"
#include "Map.h"
#include "Tile.h"
#include "GameConfig.h"

Player::Player(float startX, float startY, Color color)
{
    this->color = color;
    body = {
        startX, startY,
        static_cast<float>(TILE_SIZE),
        static_cast<float>(TILE_SIZE)};

    xVelocity = 0.0f;
    yVelocity = 0.0f;

    maxXSpeed = 10.0f;
    maxYSpeed = 15.0f;

    xAccel = 0.0f;
    yAccel = 0.0f;

    friction = 0.0f;
    gravity = 0.0f;
}

void Player::UpdateVelocity()
{
    // set friction
    if (xVelocity == 0.0f)
    {
        friction = 0.0f;
    }
    else if (xVelocity < 0.0f)
    {
        friction = 0.5f;
    }
    else if (xVelocity > 1.0f)
    {
        friction = -0.5f;
    }

    // set gravity
    if (yVelocity == 0.0f)
    {
        gravity = 0.0f;
    }
    else if (yVelocity < 0.0f)
    {
        gravity = 0.5f;
    }
    else if (yVelocity > 1.0f)
    {
        gravity = -0.5f;
    }

    // default accels are friction
    xAccel = friction;
    yAccel = gravity;

    // update xAccel based on input
    if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D))
    {
        xAccel = 0.0f;
    }
    else if (IsKeyDown(KEY_A))
    {
        xAccel = -1.0f;
    }
    else if (IsKeyDown(KEY_D))
    {
        xAccel = 1.0f;
    }

    // update yAccel based on input
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_S))
    {
        yAccel = 0.0f;
    }
    else if (IsKeyDown(KEY_W))
    {
        yAccel = -1.0f;
    }
    else if (IsKeyDown(KEY_S))
    {
        yAccel = 1.0f;
    }

    // check maxSpeed before applying accel
    if (std::abs(xVelocity + xAccel) <= maxXSpeed)
    {
        xVelocity += xAccel;
    }

    if (std::abs(yVelocity + yAccel) <= maxXSpeed)
    {
        yVelocity += yAccel;
    }
}

void Player::CollisionCheck(const Map &map)
{
    std::optional<Rectangle> collidingRect;
    Rectangle tempChecker = {
        body.x + xVelocity,
        body.y + yVelocity,
        TILE_SIZE,
        TILE_SIZE};

    for (int i = 0; i < WINDOW_TILE_WIDTH; i++)
    {
        for (int j = 0; j < WINDOW_TILE_HEIGHT; j++)
        {
            if (CheckCollisionRecs(tempChecker, map.getTile(i, j).getBody()) && map.getTile(i, j).getID() == 1)
            {
                collidingRect = map.getTile(i, j).getBody();
            }
        }
    }

    if (collidingRect.has_value())
    {
        float xDelta = tempChecker.x - collidingRect->x;
        float yDelta = tempChecker.y - collidingRect->y;

        xVelocity = xDelta;
        yVelocity = yDelta;
    }
}

void Player::Update(const Map &map)
{
    UpdateVelocity();
    // CollisionCheck(map);

    body.x += xVelocity;
    body.y += yVelocity;
}

void Player::Draw()
{
    DrawRectangle(
        static_cast<int>(std::round(body.x)),
        static_cast<int>(std::round(body.y)),
        static_cast<int>(body.width),
        static_cast<int>(body.height),
        color);
}

void Player::DrawDebug()
{
    DrawText(
        TextFormat(
            "xPos: %.2f\nyPos: %.2f\nxVel: %.2f\nyVel: %.2f\nxAccel: %.2f\nyAccel: %.2f",
            body.x,
            body.y,
            xVelocity,
            yVelocity,
            xAccel,
            yAccel),
        10, 10,
        32,
        WHITE);
}