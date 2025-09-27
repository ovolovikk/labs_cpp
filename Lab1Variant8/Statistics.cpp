#include "Statistics.h"
#include "Board.h"
#include "CellGenerator.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>

double Statistics::calculateMean(const std::vector<int>& values) 
{
    if (values.empty()) 
    {
        throw std::invalid_argument("Cannot calculate mean of empty vector");
    }
    
    long long sum = std::accumulate(values.begin(), values.end(), 0LL);
    return static_cast<double>(sum) / values.size();
}

double Statistics::calculateMedian(std::vector<int>& values) 
{
    if (values.empty()) 
    {
        throw std::invalid_argument("Cannot calculate median of empty vector");
    }
    
    std::sort(values.begin(), values.end());
    size_t size = values.size();
    
    if (size % 2 == 0) 
    {
        return (values[size / 2 - 1] + values[size / 2]) / 2.0;
    } else 
        {
        return values[size / 2];
        }
}

std::pair<double, double> Statistics::runExperiment(int n, int k, int trials, unsigned int seed)
{
    if (n <= 0) 
    {
        throw std::invalid_argument("Board size must be positive");
    }
    if (k < 0) 
    {
        throw std::invalid_argument("Number of selections cannot be negative");
    }
    if (trials <= 0) 
    {
        throw std::invalid_argument("Number of trials must be positive");
    }
    
    std::vector<int> free_zone_sizes;
    free_zone_sizes.reserve(trials);
    
    Board board(n);
    CellGenerator cell_gen(n, seed);
    
    for (int trial = 0; trial < trials; trial++) 
    {
        board.reset();
        
        for (int selection = 0; selection < k; selection++) 
        {
            auto [row, col] = cell_gen();
            board.addSelectedCell(row, col);
        }
        
        int free_zone_size = board.calculateFreeZoneSize();
        free_zone_sizes.push_back(free_zone_size);
    }
    
    double mean = calculateMean(free_zone_sizes);
    double median = calculateMedian(free_zone_sizes);
    
    return {mean, median};
}