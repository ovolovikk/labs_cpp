
#include "Board.h"
#include <stdexcept>

Board::Board(int n) : size(n)
{
    //TOBEDONE
}

void Board::addSelectedCell(int row, int col)
{
    //TOBEDONE
}

void Board::reset()
{
    //TOBEDONE
}

bool Board::isInBounds(int row, int col) const
{
    //TOBEDONE
}

int Board::calculateFreeZoneSize() const
{
    //TOBEDONE
}

bool Board::isAdjacentToSelected(int row, int col) const {
    const int dr[] = {-1, 0, 0, 1};  // up, left, right, down
    const int dc[] = {0, -1, 1, 0};  // up, left, right, down
    
    // First check if the cell itself is selected
    if (selected_cells.count({row, col}) > 0) {
        return true;
    }
    
    // Then check adjacent cells
    for (int i = 0; i < 4; i++) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];
        
        if (isInBounds(new_row, new_col)) {
            if (selected_cells.count({new_row, new_col}) > 0) {
                return true;
            }
        }
    }
    
    return false;
}