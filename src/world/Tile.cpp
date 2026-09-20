#include <raylib.h>

#include "GameConfig.h"
#include "world/Tile.h"

Tile::Tile()
    : id(-1),
      body{0.0f, 0.0f, 0.0f, 0.0f}
{
}

Tile::Tile(int id, Rectangle body)
    : id(id),
      body(body)
{
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
    return TILE_PROPERTIES[id].color;
}

bool Tile::isSolid() const {
    return TILE_PROPERTIES[id].isSolid;
}