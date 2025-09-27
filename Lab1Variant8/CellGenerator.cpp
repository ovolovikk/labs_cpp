#include "CellGenerator.h"
#include <stdexcept>

CellGenerator::CellGenerator(int n, unsigned seed)
    : board_size(n), generator(seed), distribution(0, n - 1)
{
    if(n <= 0)
    {
        throw std::invalid_argument("Board size must be positive number");
    }
}

std::pair<int, int> CellGenerator::operator()() const
{
    int row = distribution(generator);
    int col = distribution(generator);
    return {row, col};
}
