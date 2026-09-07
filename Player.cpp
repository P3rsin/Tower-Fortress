#include "Player.h"
#include "GameConfig.h"
#include <raylib.h>

Player::Player(int startX, int startY)
{
    x = startX;
    y = startY;

    xSpeed = 5;
    ySpeed = 5;

    xAccel = 1;
    yAccel = 1;
}

void Player::Update()
{
    if (IsKeyDown(KEY_RIGHT))
    {
        x += xSpeed;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        x -= xSpeed;
    }
    if (IsKeyDown(KEY_UP))
    {
        y -= ySpeed;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        y += ySpeed;
    }
}

void Player::Draw()
{
    DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, RED);
}