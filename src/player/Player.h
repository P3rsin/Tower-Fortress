#pragma once
#include <vector>
#include <raylib.h>

#include "world/Map.h"

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
    bool CollisionCheck(const Map &map);

    std::vector<std::string> collisionDebug;

public:
    Player(float startX, float startY, Color color);
    void Update(const Map &map);
    void Draw();
    void DrawDebug();
};