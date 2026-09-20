#include <raylib.h>

#include "GameConfig.h"
#include "world/Tile.h"

Tile::Tile(int id, Rectangle body)
    : id(id),
      body(body),
      color(TILE_COLORS[id])
{
}

void Tile::setColor(const Color &color)
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

const Color &Tile::getColor() const
{
    return color;
}