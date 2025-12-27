#include "GameOfLife.h"
#include <cstdlib>
#include <ctime>

GameOfLife::GameOfLife() {
    grid.resize(GameConstants::GridRows * GameConstants::GridCols);
    nextGrid.resize(GameConstants::GridRows * GameConstants::GridCols);
    Initialize();
}

void GameOfLife::Initialize() {
    
    for (int& cell : grid) {
        cell = rand() % 2;
    }
}

void GameOfLife::Reset() {
    Initialize();
}

bool GameOfLife::IsAlive(int row, int col) const {
    if (row < 0 || row >= GameConstants::GridRows || col < 0 || col >= GameConstants::GridCols) {
        return false;
    }
    return grid[row * GameConstants::GridCols + col] == 1;
}

int GameOfLife::CountNeighbors(int row, int col) const {
    int livingNeighborCount = 0;
    
    int dRow[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dCol[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; ++i) {
        int nx = (row + dRow[i] + GameConstants::GridRows) % GameConstants::GridRows;
        int ny = (col + dCol[i] + GameConstants::GridCols) % GameConstants::GridCols;
        
        if (grid[nx * GameConstants::GridCols + ny] == 1) {
            livingNeighborCount++;
        }
    }

    return livingNeighborCount;
}

void GameOfLife::Update() {
    for (int i = 0; i < GameConstants::GridRows; ++i) {
        for (int j = 0; j < GameConstants::GridCols; ++j) {
            int neighbors = CountNeighbors(i, j);
            int index = i * GameConstants::GridCols + j;
            int currentState = grid[index];
            
            if (currentState == 1 && (neighbors < 2 || neighbors > 3)) {
                nextGrid[index] = 0;
            } else if (neighbors == 3 && currentState == 0) {
                nextGrid[index] = 1;
            } else {
                nextGrid[index] = currentState;
            }
        }
    }

    grid = nextGrid;
}
