#pragma once

enum class Direction{
    North = 0, // Góra (Y maleje)
    East = 1,  // Prawo (X rośnie)
    South = 2, // Dół (Y rośnie)
    West = 3   // Lewo (X maleje)
};

const float TILE_SIZE = 80.0f;