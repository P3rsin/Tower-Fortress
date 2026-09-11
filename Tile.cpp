#include <raylib.h>

#include "Tile.h"
#include "GameConfig.h"

Tile::Tile(int id, Rectangle body)
{
    this->id = id;
    this->body = body;
    color = TILE_COLORS[id];
}

void Tile::setColor(Color color)
{
    this->color = color;
}

const Rectangle &Tile::getBody() const
{
    return body;
}

int Tile::getID() const
{
    return id;
}

Color Tile::getColor() const
{
    return color;
}