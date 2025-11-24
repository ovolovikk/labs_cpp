#ifndef CELLGENERATOR_H
#define CELLGENERATOR_H

#include <random>
#include <utility>

class CellGenerator {
 private:
  int board_size;
  mutable std::mt19937 generator;
  mutable std::uniform_int_distribution<int> distribution;

 public:
  CellGenerator(int n, unsigned seed);

  std::pair<int, int> operator()() const;

  int getBoardSize() const { return board_size; }
};

#endif  // CELLGENERATOR_H
