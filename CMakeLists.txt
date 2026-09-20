cmake_minimum_required(VERSION 3.24)

project(TowerFortress LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/6.0.tar.gz
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

add_executable(TowerFortress
    src/main.cpp

    src/player/Player.cpp

    src/world/Map.cpp   
    src/world/Tile.cpp
    
    src/debug/Debug.cpp
)

target_include_directories(TowerFortress PRIVATE
    src
)

target_link_libraries(TowerFortress PRIVATE raylib)