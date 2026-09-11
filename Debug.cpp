#include "Debug.h"

namespace Debug
{
    void Clear()
    {
        std::ofstream file("GameData/output.txt", std::ios::trunc);
    }
}