#pragma once
#include <raylib.h>

class Tile
{
private:
    int id;
    Rectangle body;

public:
    Tile(int id, Rectangle body);
    Rectangle getBody();
    int getID();
};