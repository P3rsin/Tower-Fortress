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
    void setColor(Color color);
    
    const Rectangle& getBody() const;
    int getID() const;
    Color getColor() const;
};