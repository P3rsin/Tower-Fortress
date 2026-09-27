#pragma once
#include <raylib.h>

class Tile
{
public:
    Tile();
    Tile(int id, Rectangle body, bool highlighted);

    const Rectangle &getBody() const;
    int getID() const;
    void setID(int id);
    bool getHighlighted() const;
    void setHighlighted(bool isHighlighted);
    bool isSolid() const;

private:
    int id;
    Rectangle body;
    bool highlighted;
};