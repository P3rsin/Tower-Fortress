#include <vector>
#include <cmath>
#include <algorithm>
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
    float currentDeaccel;

    if (isGrounded)
    {
        currentAccel = xAccel;
        currentDeaccel = xDeaccel;
    }
    else
    {
        currentAccel = airAccel;
        currentDeaccel = airDeaccel;
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
            if (xVelocity + currentDeaccel * dt > 0.0f)
            {
                xVelocity = 0.0f;
            }
            else
            {
                xVelocity += currentDeaccel * dt;
            }
        }
        else if (xVelocity > 0.0f)
        {
            if (xVelocity - currentDeaccel * dt < 0.0f)
            {
                xVelocity = 0.0f;
            }
            else
            {
                xVelocity += -currentDeaccel * dt;
            }
        }
    }

    // coyote - player is allowed to jump
    if (isGrounded)
    {
        coyoteTimer = COYOTE_TIME;
    }
    else
    {
        coyoteTimer -= dt;
    }

    // buffer time - player wants to jump
    if (IsKeyPressed(KEY_K))
    {
        jumpBufferTimer = JUMP_BUFFER_TIME;
    }
    else
    {
        jumpBufferTimer -= dt;
    }

    // set sustainingJump if I'm within the range
    if (jumpBufferTimer > 0.0f && coyoteTimer > 0.0f)
    {
        yVelocity = -jumpSpeed;
        sustainingJump = true;

        jumpBufferTimer = 0.0f;
        coyoteTimer = 0.0f;
    }

    // if I stop holding K, stop sustainingJump
    if (sustainingJump && !IsKeyDown(KEY_K))
    {
        sustainingJump = false;
    }

    // if I stopped jumping early, fall faster
    if (!sustainingJump && yVelocity < 0.0f)
    {
        yVelocity += gravity * releasedJumpEarlyScale * dt;
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

void Player::ResolveXCollision(const Map &map, float dt)
{
    Rectangle projectedXBody = {
        body.x + xVelocity * dt,
        body.y,
        body.width,
        body.height};

    int mapPixelWidth = map.getWidth() * TILE_SIZE;

    // checking map bounds
    if (projectedXBody.x < 0.0f)
    {
        body.x = 0.0f;
        xVelocity = 0.0f;
        return;
    }
    else if (projectedXBody.x + projectedXBody.width > mapPixelWidth)
    {
        body.x = mapPixelWidth - body.width;
        xVelocity = 0.0f;
        return;
    }

    int xStart = floor(projectedXBody.x / TILE_SIZE);
    int xEnd = ceil((projectedXBody.x + projectedXBody.width) / TILE_SIZE);

    int yStart = floor(projectedXBody.y / TILE_SIZE);
    int yEnd = ceil((projectedXBody.y + projectedXBody.height) / TILE_SIZE);

    bool xColliding = false;
    float blockingX = 0.0f; // represents the relevant edge

    // otherwise, check interior tiles
    for (int i = xStart; i < xEnd; i++)
    {
        for (int j = yStart; j < yEnd; j++)
        {
            const Tile &curTile = map.getTile(i, j);

            if (!curTile.isSolid() || !CheckCollisionRecs(projectedXBody, curTile.getBody()))
            {
                continue;
            }

            if (xVelocity < 0.0f)
            {
                float candidateEdge = curTile.getBody().x + curTile.getBody().width;

                if (!xColliding || candidateEdge > blockingX)
                {
                    blockingX = candidateEdge;
                    xColliding = true;
                }
            }
            else if (xVelocity > 0.0f)
            {
                float candidateEdge = curTile.getBody().x;

                if (!xColliding || candidateEdge < blockingX)
                {
                    blockingX = candidateEdge;
                    xColliding = true;
                }
            }
        }
    }

    // if I collide, set my x
    if (xColliding)
    {
        if (xVelocity < 0.0f)
        {
            body.x = blockingX;
        }
        else if (xVelocity > 0.0f)
        {
            body.x = blockingX - body.width;
        }

        xVelocity = 0.0f;
    }
}

void Player::ResolveYCollision(const Map &map, float dt)
{
    Rectangle projectedYBody = {
        body.x,
        body.y + yVelocity * dt,
        body.width,
        body.height};

    int mapPixelHeight = map.getHeight() * TILE_SIZE;

    // checking map bonuds
    if (projectedYBody.y < 0.0f)
    {
        body.y = 0.0f;
        yVelocity = 0.0f;
        return;
    }
    else if (projectedYBody.y + projectedYBody.height > mapPixelHeight)
    {
        body.y = mapPixelHeight - body.height;
        yVelocity = 0.0f;
        isGrounded = true;
        return;
    }

    int xStart = floor(projectedYBody.x / TILE_SIZE);
    int xEnd = ceil((projectedYBody.x + projectedYBody.width) / TILE_SIZE);

    int yStart = floor(projectedYBody.y / TILE_SIZE);
    int yEnd = ceil((projectedYBody.y + projectedYBody.height) / TILE_SIZE);

    bool yColliding = false;
    float blockingY = 0.0f; // represents the relevant edge

    // otherwise, check interior tiles
    for (int i = xStart; i < xEnd; i++)
    {
        for (int j = yStart; j < yEnd; j++)
        {
            const Tile &curTile = map.getTile(i, j);

            if (!curTile.isSolid() || !CheckCollisionRecs(projectedYBody, curTile.getBody()))
            {
                continue;
            }

            if (yVelocity < 0.0f)
            {
                float candidateEdge = curTile.getBody().y + curTile.getBody().height;

                if (!yColliding || candidateEdge > blockingY)
                {
                    blockingY = candidateEdge;
                    yColliding = true;
                }
            }
            else if (yVelocity > 0.0f)
            {
                float candidateEdge = curTile.getBody().y;

                if (!yColliding || candidateEdge < blockingY)
                {
                    blockingY = candidateEdge;
                    yColliding = true;
                }
            }
        }
    }

    // if I collide, set my y
    if (yColliding)
    {
        if (yVelocity < 0.0f)
        {
            body.y = blockingY;
            hitCeiling = true;
        }
        else if (yVelocity > 0.0f)
        {
            body.y = blockingY - body.height;
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

Rectangle Player::getBody() const
{
    return body;
}

Vector2 Player::getCenter() const
{
    return {body.x + body.width / 2.0f, body.y + body.height / 2.0f};
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