#include <vector>
#include <cmath>
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
    maxSpeed = 10.0f;

    xAccel = 0.0f;
    yAccel = 0.0f;

    xFriction = 0.0f;
    yFriction = 0.0f;
}

void Player::UpdateVelocity()
{
    // set xFriction
    if (xVelocity == 0.0f)
    {
        xFriction = 0.0f;
    }
    else if (xVelocity < 0.0f)
    {
        xFriction = 0.5f;
    }
    else if (xVelocity > 1.0f)
    {
        xFriction = -0.5f;
    }

    // set yFriction
    if (yVelocity == 0.0f)
    {
        yFriction = 0.0f;
    }
    else if (yVelocity < 0.0f)
    {
        yFriction = 0.5f;
    }
    else if (yVelocity > 1.0f)
    {
        yFriction = -0.5f;
    }

    // default accels are friction
    xAccel = xFriction;
    yAccel = yFriction;

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
    if (std::abs(xVelocity + xAccel) <= maxSpeed)
    {
        xVelocity += xAccel;
    }

    if (std::abs(yVelocity + yAccel) <= maxSpeed)
    {
        yVelocity += yAccel;
    }
}

bool Player::CheckCollision(const std::vector<Tile> &tileList)
{
    bool willCollide = false;
    Rectangle tempChecker = {
        body.x + xVelocity,
        body.y + yVelocity,
        TILE_SIZE,
        TILE_SIZE};

    for (Tile tile : tileList)
    {
        if (CheckCollisionRecs(tempChecker, tile.getBody()) && tile.getID() == 0)
        {
            willCollide = true;
        }
    }

    return willCollide;
}

void Player::Update(const std::vector<Tile> &tileList)
{
    UpdateVelocity();

    if (!CheckCollision(tileList))
    {
        body.x += xVelocity;
        body.y += yVelocity;
    }
}

void Player::Draw()
{
    DrawRectangleRec(body, color);
}