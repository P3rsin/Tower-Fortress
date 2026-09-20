#include "Debug.h"

namespace Debug
{
    void Clear()
    {
        std::ofstream file("assets/debugStream.txt", std::ios::trunc);
    }
}