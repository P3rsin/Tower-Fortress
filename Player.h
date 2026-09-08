#pragma once
#include <vector>
#include "Tile.h"
#include <raylib.h>

class Player
{
private:
    Rectangle body;
    Color color;

    float xSpeed;
    float ySpeed;

    float xAccel;
    float yAccel;

public:
    Player(float startX, float startY, Color color);
    void Update(const std::vector<Tile>);
    void Draw();
};