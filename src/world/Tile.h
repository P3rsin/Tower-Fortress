#pragma once
#include <raylib.h>

class Tile
{
private:
    int id;
    Rectangle body;
    Color color;

public:
    Tile(int id, Rectangle body);

    void setColor(const Color &color);
    const Rectangle &getBody() const;
    int getID() const;
    const Color &getColor() const;
};