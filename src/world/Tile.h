#pragma once
#include <raylib.h>

struct TileCoord
{
    int x;
    int y;
};

class Tile
{
public:
    Tile();
    Tile(int id, Rectangle body);

    const Rectangle &getBody() const;
    int getID() const;
    void setID(int id);
    bool isSolid() const;

private:
    int id;
    Rectangle body;
};