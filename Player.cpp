#include <vector>
#include <cmath>
#include <optional>
#include <raylib.h>

#include "Player.h"
#include "Map.h"
#include "Tile.h"
#include "GameConfig.h"
#include "Debug.h"

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
    maxYSpeed = 10.0f;

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
    else
    {
        xVelocity = maxXSpeed;
    }

    if (std::abs(yVelocity + yAccel) <= maxYSpeed)
    {
        yVelocity += yAccel;
    }
    else
    {
        yVelocity = maxYSpeed;
    }
}

bool Player::CollisionCheck(const Map &map)
{
    collisionDebug.clear();

    Rectangle projectedBody = {
        body.x + xVelocity,
        body.y + yVelocity,
        TILE_SIZE,
        TILE_SIZE};

    int xstart = floor(projectedBody.x / TILE_SIZE);
    int xend = ceil((projectedBody.x + projectedBody.width) / TILE_SIZE);

    int ystart = floor(projectedBody.y / TILE_SIZE);
    int yend = ceil((projectedBody.y + projectedBody.height) / TILE_SIZE);

    // std::optional<Rectangle> collidingRect;
    bool willCollide = false;
    for (int i = xstart; i < xend; i++)
    {
        for (int j = ystart; j < yend; j++)
        {
            Tile curTile = map.getTile(i, j);

            collisionDebug.push_back(
                "Tile (" + std::to_string(i) + ", " + std::to_string(j) + ")" +
                " | ID: " + std::to_string(curTile.getID()) +
                " | Position: (" +
                std::to_string(curTile.getBody().x) + ", " +
                std::to_string(curTile.getBody().y) + ")");

            if (CheckCollisionRecs(projectedBody, curTile.getBody()) && curTile.getID() == 0)
            {
                willCollide = true;
            }
        }
    }

    // if (collidingRect.has_value())
    // {
    //     float xDelta = projectedBody.x - collidingRect->x;
    //     float yDelta = projectedBody.y - collidingRect->y;

    //     xVelocity = xDelta;
    //     yVelocity = yDelta;
    // }

    Debug::Clear();
    return willCollide;
}

void Player::Update(const Map &map)
{
    UpdateVelocity();
    if (!CollisionCheck(map))
    {
        body.x += xVelocity;
        body.y += yVelocity;
    }
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

    int y = 220;

    for (const std::string &line : collisionDebug)
    {
        DrawText(
            line.c_str(),
            10,
            y,
            20,
            WHITE);

        y += 25;
    }
}