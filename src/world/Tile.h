#pragma once
#include <raylib.h>

class Tile
{
public:
    Tile();
    Tile(int id, Rectangle body);

    const Rectangle &getBody() const;
    int getID() const;
    const Color &getColor() const;
    bool isSolid() const;

private:
    int id;
    Rectangle body;
};