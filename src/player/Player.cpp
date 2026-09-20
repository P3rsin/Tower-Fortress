#include <vector>
#include <cmath>
#include <optional>
#include <raylib.h>

#include "GameConfig.h"
#include "world/Map.h"
#include "world/Tile.h"
#include "player/Player.h"
#include "debug/Debug.h"

Player::Player(float startX, float startY, Color color)
    : body{startX, startY,
           static_cast<float>(TILE_SIZE),
           static_cast<float>(TILE_SIZE)},
      color(color)
{
}

void Player::UpdateVelocity()
{
    // set xDeaccel
    if (xVelocity == 0.0f)
    {
        xDeaccel = 0.0f;
    }
    else if (xVelocity < 0.0f)
    {
        xDeaccel = 0.5f;

        if (xDeaccel + xVelocity > 0.0f)
        {
            xDeaccel = -xVelocity;
        }
    }
    else if (xVelocity > 0.0f)
    {
        xDeaccel = -0.5f;

        if (xDeaccel + xVelocity < 0.0f)
        {
            xDeaccel = -xVelocity;
        }
    }

    // set yDeaccel
    if (yVelocity == 0.0f)
    {
        yDeaccel = 0.0f;
    }
    else if (yVelocity < 0.0f)
    {
        yDeaccel = 0.5f;

        if (yDeaccel + yVelocity > 0.0f)
        {
            yDeaccel = -yVelocity;
        }
    }
    else if (yVelocity > 0.0f)
    {
        yDeaccel = -0.5f;

        if (yDeaccel + yVelocity < 0.0f)
        {
            yDeaccel = -yVelocity;
        }
    }

    // update xAccel based on input, default xDeaccel
    if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
    {
        xAccel = -1.0f;
    }
    else if (!IsKeyDown(KEY_A) && IsKeyDown(KEY_D))
    {
        xAccel = 1.0f;
    }
    else
    {
        xAccel = xDeaccel;
    }

    // update yAccel based on input, default yDeaccel
    if (IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))
    {
        yAccel = -1.0f;
    }
    else if (!IsKeyDown(KEY_W) && IsKeyDown(KEY_S))
    {
        yAccel = 1.0f;
    }
    else
    {
        yAccel = yDeaccel;
    }

    // check maxXSpeed before applying accel
    if (std::abs(xVelocity + xAccel) <= maxXSpeed)
    {
        xVelocity += xAccel;
    }
    else if (xVelocity < 0.0f)
    {
        xVelocity = -maxXSpeed;
    }
    else
    {
        xVelocity = maxXSpeed;
    }

    // check maxYSpeed before applying accel
    if (std::abs(yVelocity + yAccel) <= maxYSpeed)
    {
        yVelocity += yAccel;
    }
    else if (yVelocity < 0.0f)
    {
        yVelocity = -maxYSpeed;
    }
    else
    {
        yVelocity = maxYSpeed;
    }
}

void Player::ResolveXCollision(const Map &map)
{
    collisionDebug.clear();

    Rectangle projectedXBody = {
        body.x + xVelocity,
        body.y,
        TILE_SIZE,
        TILE_SIZE};

    int xStart = floor(projectedXBody.x / TILE_SIZE);
    int xEnd = ceil((projectedXBody.x + projectedXBody.width) / TILE_SIZE);

    int yStart = floor(projectedXBody.y / TILE_SIZE);
    int yEnd = ceil((projectedXBody.y + projectedXBody.height) / TILE_SIZE);

    xColliding = false;
    Tile collidingTile;

    for (int i = xStart; i < xEnd; i++)
    {
        for (int j = yStart; j < yEnd; j++)
        {
            Tile curTile = map.getTile(i, j);

            collisionDebug.push_back(
                "Tile (" + std::to_string(i) + ", " + std::to_string(j) + ")" +
                " | ID: " + std::to_string(curTile.getID()) +
                " | Position: (" +
                std::to_string(curTile.getBody().x) + ", " +
                std::to_string(curTile.getBody().y) + ")");

            if (CheckCollisionRecs(projectedXBody, curTile.getBody()) && curTile.isSolid())
            {
                xColliding = true;
                collidingTile = curTile;
            }
        }
    }

    if (xColliding && collidingTile.getBody().x < body.x)
    {
        xVelocity = collidingTile.getBody().x + collidingTile.getBody().width - body.x;
    }
    else if (xColliding && collidingTile.getBody().x > body.x)
    {
        xVelocity = collidingTile.getBody().x - (body.x + body.width);
    }

    Debug::Clear();
}

void Player::ResolveYCollision(const Map &map)
{
    Rectangle projectedYBody = {
        body.x,
        body.y + yVelocity,
        TILE_SIZE,
        TILE_SIZE};

    int xStart = floor(projectedYBody.x / TILE_SIZE);
    int xEnd = ceil((projectedYBody.x + projectedYBody.width) / TILE_SIZE);

    int yStart = floor(projectedYBody.y / TILE_SIZE);
    int yEnd = ceil((projectedYBody.y + projectedYBody.height) / TILE_SIZE);

    yColliding = false;
    Tile collidingTile;

    for (int i = xStart; i < xEnd; i++)
    {
        for (int j = yStart; j < yEnd; j++)
        {
            Tile curTile = map.getTile(i, j);

            if (CheckCollisionRecs(projectedYBody, curTile.getBody()) && curTile.isSolid())
            {
                yColliding = true;
                collidingTile = curTile;
            }
        }
    }

    if (yColliding && collidingTile.getBody().y < body.y)
    {
        yVelocity = collidingTile.getBody().y + collidingTile.getBody().height - body.y;
    }
    else if (yColliding && collidingTile.getBody().y > body.y)
    {
        yVelocity = collidingTile.getBody().y - (body.y + body.height);
    }
}

void Player::Update(const Map &map)
{
    UpdateVelocity();

    ResolveXCollision(map);
    ResolveYCollision(map);

    body.x += xVelocity;
    body.y += yVelocity;
}

void Player::Draw() const
{
    DrawRectangle(
        static_cast<int>(std::round(body.x)),
        static_cast<int>(std::round(body.y)),
        static_cast<int>(body.width),
        static_cast<int>(body.height),
        color);
}

void Player::DrawDebug() const
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