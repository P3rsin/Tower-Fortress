#include <vector>
#include <cmath>
#include <raylib.h>

#include "GameConfig.h"
#include "world/Map.h"
#include "world/Tile.h"
#include "player/Player.h"
#include "debug/Debug.h"

Player::Player(float startX, float startY, float width, float height, Color color)
    : body{startX, startY, width, height},
      color(color)
{
}

void Player::UpdateVelocity(float dt)
{
    // pick the appropriate acceleration
    float currentAccel;

    if (isGrounded)
    {
        currentAccel = xAccel;
    }
    else
    {
        currentAccel = airAccel;
    }

    // I'm moving, so apply currentAccel based on input
    if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
    {
        xVelocity += -currentAccel * dt;
    }
    else if (!IsKeyDown(KEY_A) && IsKeyDown(KEY_D))
    {
        xVelocity += currentAccel * dt;
    }
    else // either A && D or !A && !D, so apply xDeaccel
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

    // set rising if I can jump
    if (IsKeyPressed(KEY_K) && isGrounded)
    {
        preJumpY = body.y;
        yVelocity = -jumpSpeed;
        rising = true;
    }

    // if I'm rising, rise until I hit my limit
    if (rising)
    {
        if (!IsKeyDown(KEY_K))
        {
            rising = false;
        }

        if (preJumpY - body.y >= maxJumpHeight)
        {
            rising = false;
            yVelocity = 0.0f;
        }
    }

    // if I stopped jumping early, fall faster
    if (!rising && yVelocity < 0.0f)
    {
        yVelocity += gravity * relasedJumpEarlyScale * dt;
    }
    else // general gravity applied
    {
        yVelocity += gravity * dt;
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
    if (yVelocity > maxFallSpeed)
    {
        yVelocity = maxFallSpeed;
    }
}

// keep in mind collidingTile refers to the last detected
// collision, not the nearest, change eventually
void Player::ResolveXCollision(const Map &map, float dt)
{
    collisionDebug.clear();

    Rectangle projectedXBody = {
        body.x + xVelocity * dt,
        body.y,
        body.width,
        body.height};

    int xStart = floor(projectedXBody.x / TILE_SIZE);
    int xEnd = ceil((projectedXBody.x + projectedXBody.width) / TILE_SIZE);

    int yStart = floor(projectedXBody.y / TILE_SIZE);
    int yEnd = ceil((projectedXBody.y + projectedXBody.height) / TILE_SIZE);

    xColliding = false;
    Tile collidingTile;

    // checking map bounds
    if (!map.isInBounds(xStart, yStart))
    {
        xColliding = true;
        Rectangle temp = {-TILE_SIZE, body.y, TILE_SIZE, TILE_SIZE};
        collidingTile = Tile(0, temp);
    }
    else if (!map.isInBounds(xEnd - 1, yEnd - 1))
    {
        xColliding = true;
        Rectangle temp = {WINDOW_TILE_WIDTH * TILE_SIZE, body.y, TILE_SIZE, TILE_SIZE};
        collidingTile = Tile(0, temp);
    }
    else
    {
        // checking general tiles
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
    }

    // if I collide, set my x
    if (xColliding)
    {
        if (xVelocity < 0.0f)
        {
            body.x = collidingTile.getBody().x + collidingTile.getBody().width;
        }
        else if (xVelocity > 0.0f)
        {
            body.x = collidingTile.getBody().x - body.width;
        }

        xVelocity = 0.0f;
    }

    Debug::Clear();
}

// keep in mind collidingTile refers to the last detected
// collision, not the nearest, change eventually
void Player::ResolveYCollision(const Map &map, float dt)
{
    Rectangle projectedYBody = {
        body.x,
        body.y + yVelocity * dt,
        body.width,
        body.height};

    int xStart = floor(projectedYBody.x / TILE_SIZE);
    int xEnd = ceil((projectedYBody.x + projectedYBody.width) / TILE_SIZE);

    int yStart = floor(projectedYBody.y / TILE_SIZE);
    int yEnd = ceil((projectedYBody.y + projectedYBody.height) / TILE_SIZE);

    yColliding = false;
    Tile collidingTile;

    // checking map bonuds
    if (!map.isInBounds(xStart, yStart))
    {
        yColliding = true;
        Rectangle temp = {body.x, -TILE_SIZE, TILE_SIZE, TILE_SIZE};
        collidingTile = Tile(0, temp);
    }
    else if (!map.isInBounds(xEnd - 1, yEnd - 1))
    {
        yColliding = true;
        Rectangle temp = {body.x, WINDOW_TILE_HEIGHT * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        collidingTile = Tile(0, temp);
    }
    else
    {
        // checking general tiles
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
    }

    // if I collide, set my y
    if (yColliding)
    {
        if (yVelocity < 0.0f)
        {
            body.y = collidingTile.getBody().y + collidingTile.getBody().height;
            hitCeiling = true;
        }
        else if (yVelocity > 0.0f)
        {
            body.y = collidingTile.getBody().y - body.height;
            isGrounded = true;
        }

        yVelocity = 0.0f;
    }
}

void Player::Update(const Map &map)
{
    float dt = GetFrameTime();
    dt = std::min(dt, 0.05f); // in case of a frame hitch

    UpdateVelocity(dt);

    // resolve x
    ResolveXCollision(map, dt);
    body.x += xVelocity * dt;

    // resolve y
    isGrounded = false;
    hitCeiling = false;

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
            "xPos: %.2f\nyPos: %.2f\nxVel: %.2f\nyVel: %.2f\nxAccel: %.2f",
            body.x,
            body.y,
            xVelocity,
            yVelocity,
            xAccel),
        10, 10,
        32,
        WHITE);

    int y = 210;

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