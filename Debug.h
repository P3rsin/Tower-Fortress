#pragma once

#include <fstream>

namespace Debug
{
    void Clear()
    {
        std::ofstream file("GameData/output.txt", std::ios::trunc);
    };

    template <typename T>
    void Write(const T &value)
    {
        std::ofstream file("GameData/output.txt", std::ios::app);
        file << value << '\n';
    }
}