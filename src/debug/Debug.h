#pragma once

#include <fstream>

namespace Debug
{
    void Clear();

    template <typename T>
    void Write(const T &value)
    {
        std::ofstream file("GameData/debugStream.txt", std::ios::app);
        file << value << '\n';
    }
}