#include <vector>
#include <cmath>
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

// if I'm moving, velocity = +-accel
// if I'm not moving velocity = +-deaccel

void Player::UpdateVelocity(float dt)
{
    // I'm moving, apply xAccel based on input
    if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
    {
        xVelocity += -xAccel * dt;
    }
    else if (!IsKeyDown(KEY_A) && IsKeyDown(KEY_D))
    {
        xVelocity += xAccel * dt;
    }
    else // either A && D or !A && !D, apply xDeaccel
    {
        if (xVelocity < 0.0f)
        {
            if (xVelocity + xDeaccel * dt > 0.0f)
            {
                xVelocity = 0.0f;
            }
            else
            {
                xVelocity += xDeaccel * dt;
            }
        }
        else if (xVelocity > 0.0f)
        {
            if (xVelocity - xDeaccel * dt < 0.0f)
            {
                xVelocity = 0.0f;
            }
            else
            {
                xVelocity -= xDeaccel * dt;
            }
        }
    }

    // I'm moving, apply yAccel based on input
    if (IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))
    {
        yVelocity += -yAccel * dt;
    }
    else if (!IsKeyDown(KEY_W) && IsKeyDown(KEY_S))
    {
        yVelocity += yAccel * dt;
    }
    else // either W && S or !W && !S, apply yDeaccel
    {
        if (yVelocity < 0.0f)
        {
            if (yVelocity + yDeaccel * dt > 0.0f)
            {
                yVelocity = 0.0f;
            }
            else
            {
                yVelocity += yDeaccel * dt;
            }
        }
        else if (yVelocity > 0.0f)
        {
            if (yVelocity - yDeaccel * dt < 0.0f)
            {
                yVelocity = 0.0f;
            }
            else
            {
                yVelocity -= yDeaccel * dt;
            }
        }
    }

    // check maxXSpeed
    if (std::abs(xVelocity) > maxXSpeed)
    {
        if (xVelocity < 0.0f)
        {
            xVelocity = -maxXSpeed;
        }
        else
        {
            xVelocity = maxXSpeed;
        }
    }

    // check maxYSpeed
    if (std::abs(yVelocity) > maxYSpeed)
    {
        if (yVelocity < 0.0f)
        {
            yVelocity = -maxYSpeed;
        }
        else
        {
            yVelocity = maxYSpeed;
        }
    }
}

void Player::ResolveXCollision(const Map &map, float dt)
{
    collisionDebug.clear();

    Rectangle projectedXBody = {
        body.x + xVelocity * dt,
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
            const Tile &curTile = map.getTile(i, j);

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
        body.x = collidingTile.getBody().x + collidingTile.getBody().width;
        xVelocity = 0.0f;
    }
    else if (xColliding && collidingTile.getBody().x > body.x)
    {
        body.x = collidingTile.getBody().x - body.width;
        xVelocity = 0.0f;
    }

    Debug::Clear();
}

void Player::ResolveYCollision(const Map &map, float dt)
{
    Rectangle projectedYBody = {
        body.x,
        body.y + yVelocity * dt,
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
            const Tile &curTile = map.getTile(i, j);

            if (CheckCollisionRecs(projectedYBody, curTile.getBody()) && curTile.isSolid())
            {
                yColliding = true;
                collidingTile = curTile;
            }
        }
    }

    if (yColliding && collidingTile.getBody().y < body.y)
    {
        body.y = collidingTile.getBody().y + collidingTile.getBody().height;
        yVelocity = 0.0f;
    }
    else if (yColliding && collidingTile.getBody().y > body.y)
    {
        body.y = collidingTile.getBody().y - body.height;
        yVelocity = 0.0f;
    }
}

void Player::Update(const Map &map)
{
    float dt = GetFrameTime();
    UpdateVelocity(dt);

    ResolveXCollision(map, dt);
    body.x += xVelocity * dt;

    ResolveYCollision(map, dt);
    body.y += yVelocity * dt;
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