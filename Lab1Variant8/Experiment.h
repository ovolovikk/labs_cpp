#pragma once

#include <string>
#include <utility>

// Class for managing experiments and parameter sweeps
class Experiment 
{
public:
    static void runSingle(int n, int k, int trials, unsigned int seed);
    
    static void runSweep(int n, int trials, unsigned int seed, 
                         int k_max, int step, const std::string& output_file);
    
    static void printUsage(const char* prog);
};
