#include "Experiment.h"
#include "Statistics.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

void Experiment::runSingle(int n, int k, int trials, unsigned int seed) 
{
    auto [mean, median] = Statistics::runExperiment(n, k, trials, seed);
    
    std::cout << "Single run: n = " << n << ", k = " << k << ", trials=" << trials 
              << ", seed=" << seed << "\n";
    std::cout << "Mean free zone size = " << mean << "\n";
    std::cout << "Median free zone size = " << median << "\n";
    std::cout << "Board cells total = " << static_cast<long long>(n) * n << "\n";
}

void Experiment::runSweep(int n, int trials, unsigned int seed, 
                         int k_max, int step, const std::string& output_file) 
{
    if (k_max < 0)
    {
        throw std::invalid_argument("k_max must be >= 0");
    }
    if (step <= 0)
    {
        throw std::invalid_argument("step must be > 0");
    }
    
    std::ofstream fout(output_file);
    if (!fout)
    {
        throw std::runtime_error("Cannot open output file: " + output_file);
    }
    
    fout << "k,mean_free_zone,median_free_zone\n";
    
    std::cout << "Sweep: n = " << n << ", trials = " << trials << ", seed =" << seed 
              << ", k from 0 to " << k_max << " step " << step << "\n";
    
    for (int k = 0; k <= k_max; k += step)
    {
        auto [mean, median] = Statistics::runExperiment(n, k, trials, seed + k);
        
        std::cout << "k = " << k << ": mean = " << mean << ", median = " << median << "\n";
        fout << k << ", " << mean << ", " << median << "\n";
    }
    
    fout.close();
    std::cout << "Sweep results written to " << output_file << "\n";
}

void Experiment::printUsage(const char* prog) 
{
    std::cout << "Usage:\n"
              << "  " << prog << " n k trials [seed]\n"
              << "  " << prog << " n k trials [seed] --sweep k_max step out.csv\n\n"
              << "Examples:\n"
              << "  " << prog << " 20 10 10000\n"
              << "  " << prog << " 20 0 1000 42 --sweep 200 5 sweep.csv\n";
}
