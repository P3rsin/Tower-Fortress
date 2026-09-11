#pragma once
#include <vector>
#include <raylib.h>

#include "Tile.h"

class Player
{
private:
    Rectangle body;
    Color color;

    float xVelocity;
    float yVelocity;
    float maxSpeed;
    // maxSpeed vector magnitude vs independent axis 

    float xAccel;
    float yAccel;

    float xFriction;
    float yFriction;

    void UpdateVelocity();
    bool CheckCollision(const std::vector<Tile>&);

public:
    Player(float startX, float startY, Color color);
    void Update(const std::vector<Tile>&);
    void Draw();
};