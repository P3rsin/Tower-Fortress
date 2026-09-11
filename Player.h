#pragma once
#include <vector>
#include <raylib.h>

#include "Map.h"

class Player
{
private:
    Rectangle body;
    Color color;

    float xVelocity;
    float yVelocity;

    float maxXSpeed;
    float maxYSpeed;

    float xAccel;
    float yAccel;

    float friction;
    float gravity;

    void UpdateVelocity();
    void CollisionCheck(const Map &map);

public:
    Player(float startX, float startY, Color color);
    void Update(const Map &map);
    void Draw();
    void DrawDebug();
};