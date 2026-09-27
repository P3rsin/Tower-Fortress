#include <raylib.h>

#include "GameConfig.h"
#include "world/Tile.h"

Tile::Tile()
    : id(-1),
      body{0.0f, 0.0f, 0.0f, 0.0f},
      highlighted(false)
{
}

Tile::Tile(int id, Rectangle body, bool highlighted)
    : id(id),
      body(body),
      highlighted(highlighted)
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

void Tile::setID(int id)
{
    this->id = id;
}

bool Tile::getHighlighted() const
{
    return highlighted;
}

void Tile::setHighlighted(bool isHighlighted)
{
    this->highlighted = isHighlighted;
}

bool Tile::isSolid() const
{
    return TILE_PROPERTIES[id].isSolid;
}