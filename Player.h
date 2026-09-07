#pragma once

class Player
{
private:
    int x;
    int y;

    int xSpeed;
    int ySpeed;

    int xAccel;
    int yAccel;

public:
    Player(int startX, int startY);
    void Update();
    void Draw();
};