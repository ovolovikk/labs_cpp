#include "Board.h"

#include <stdexcept>

Board::Board(int n) : size(n) {
  if (n <= 0) {
    throw std::invalid_argument("Board size must be positive");
  }
  reset();
}

void Board::addSelectedCell(int row, int col) {
  if (!isInBounds(row, col)) {
    throw std::out_of_range("Cell coordinates out of board range");
  }
  selected_cells.emplace(row, col);
}

void Board::reset() { selected_cells.clear(); }

bool Board::isInBounds(int row, int col) const {
  return row >= 0 && row < size && col >= 0 && col < size;
}

int Board::calculateFreeZoneSize() const {
  int free_zone = 0;
  for (int r = 0; r < size; ++r) {
    for (int c = 0; c < size; ++c) {
      if (!isAdjacentToSelected(r, c)) {
        free_zone++;
      }
    }
  }
  return free_zone;
}

bool Board::isAdjacentToSelected(int row, int col) const {
  const int dr[] = {-1, 0, 0, 1};  // up, left, right, down
  const int dc[] = {0, -1, 1, 0};  // up, left, right, down

  // TODO(@ovolovikk): use contains from C++20
  if (selected_cells.contains({row, col})) {
    return true;
  }

  for (int i = 0; i < 4; i++) {
    // TODO(@ovolovikk): use const auto
    const auto new_row = row + dr[i];
    const auto new_col = col + dc[i];

    if (isInBounds(new_row, new_col)) {
      if (selected_cells.contains({new_row, new_col})) {
        return true;
      }
    }
  }

  return false;
}
