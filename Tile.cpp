#include "Tile.h"
#include <raylib.h>

Tile::Tile(int id, Rectangle body)
{
    this->id = id;
    this->body = body;
}

Rectangle Tile::getBody() {
    return body;
}

int Tile::getID() {
    return id;
}