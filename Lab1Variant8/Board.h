// TODO(@ovolovikk): use portable include guard
#ifndef BOARD_H
#define BOARD_H

// TODO(@ovolovikk): sort your includes
#include <set>
#include <utility>
#include <vector>

class Board {
 private:
  int size;
  std::set<std::pair<int, int>> selected_cells;

  bool isAdjacentToSelected(int row, int col) const;

  bool isInBounds(int row, int col) const;

 public:
  explicit Board(int n);

  void addSelectedCell(int row, int col);

  void reset();

  int calculateFreeZoneSize() const;

  int getTotalCells() const { return size * size; }

  int getSize() const { return size; }

  size_t getSelectedCount() const { return selected_cells.size(); }
};

#endif  // BOARD_H