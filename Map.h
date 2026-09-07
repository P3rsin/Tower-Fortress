#pragma once

#include <string>
#include <vector>

class Map
{
private:
    std::vector<std::string> mapData;

public:
    void Load(std::string filePath);
    void Draw();
};