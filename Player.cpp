#include "Player.h"
#include "Map.h"
#include "GameConfig.h"
#include <raylib.h>

Player::Player(float startX, float startY, Color color)
{
    this->color = color;
    body = {
        startX, startY,
        static_cast<float>(TILE_SIZE),
        static_cast<float>(TILE_SIZE)};

    xSpeed = 5.0f;
    ySpeed = 5.0f;

    xAccel = 1.0f;
    yAccel = 1.0f;
}

void Player::Update()
{
    if (IsKeyDown(KEY_RIGHT))
    {
        body.x += xSpeed;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        body.x -= xSpeed;
    }
    if (IsKeyDown(KEY_UP))
    {
        body.y -= ySpeed;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        body.y += ySpeed;
    }
}

void Player::Draw()
{
    DrawRectangleRec(body, color);
}