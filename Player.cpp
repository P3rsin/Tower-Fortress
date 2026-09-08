#include "Player.h"
#include "GameConfig.h"
#include <raylib.h>

Player::Player(float startX, float startY, Color color)
{
    body = {startX, startY, TILE_SIZE, TILE_SIZE};
    this->color = color; 

    xSpeed = 5.0;
    ySpeed = 5.0;

    xAccel = 1.0;
    yAccel = 1.0;
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