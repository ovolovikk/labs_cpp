#pragma once

#include <vector>
#include <utility>

// Class for statistical calculations and running experiments
class Statistics 
{
public:
    static double calculateMean(const std::vector<int>& values);
    
    static double calculateMedian(std::vector<int>& values);
    
    static std::pair<double, double> runExperiment(int n, int k, int trials, unsigned int seed);
    
};
