#pragma once
#include <vector>
#include "Constants.h"

class GameOfLife {
public:
    GameOfLife();
    void Initialize();
    void Update();
    bool IsAlive(int row, int col) const;
    void Reset();

private:
    int CountNeighbors(int row, int col) const;
    
    std::vector<int> grid;
    std::vector<int> nextGrid;
};
