#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>
#include <fstream>
#include <limits>

#include "Timer.h"
#include "CustomParallel.h"

std::vector<int> generate_data(size_t size) 
{
    std::cout << "Generating " << size << " elements...\n";
    std::vector<int> data;
    data.reserve(size);
    std::mt19937 gen(1337); // seed
    std::uniform_int_distribution<> distrib(0, 1000000000);
    for (size_t i = 0; i < size; ++i) 
    {
        data.push_back(distrib(gen));
    }
    return data;
}

void run_experiments(const std::vector<int>& data, std::ofstream& report_file) {
    std::cout << "\n--- Data size: " << data.size() << " ---\n";
    report_file << "\n--- Data size: " << data.size() << " ---\n";

    const int target_value = -1;
    auto predicate = [target_value](int val) { return val == target_value; };

    // lib algorithms
    { Timer t("std::any_of (sequential)"); std::any_of(data.cbegin(), data.cend(), predicate); }
    { Timer t("std::any_of (seq policy)"); std::any_of(std::execution::seq, data.cbegin(), data.cend(), predicate); }
    { Timer t("std::any_of (par policy)"); std::any_of(std::execution::par, data.cbegin(), data.cend(), predicate); }

    // parallel algorithms
    std::cout << "\nCustom parallel algorithm:\n";
    report_file << "\nCustom parallel algorithm:\n";

    std::vector<unsigned int> k_values = { 1, 2, 3, 4, 5, 6, 7, 8, 10, 12 };
    long long best_time = std::numeric_limits<long long>::max();
    unsigned int best_k = 0;

    for (unsigned int k : k_values) 
    {
        auto start = std::chrono::high_resolution_clock::now();
        custom_parallel_any_of(data.cbegin(), data.cend(), predicate, k);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "K = " << k << ", Time = " << duration << " ms\n";
        report_file << "K = " << k << ", Time = " << duration << " ms\n";

        if (duration < best_time) |
        {
            best_time = duration;
            best_k = k;
        }
    }

    unsigned int hardware_threads = std::thread::hardware_concurrency();
    std::cout << "\nBest K: " << best_k << "\n";
    std::cout << "Hardware threads: " << hardware_threads << "\n";
    std::cout << "Ratio (K/threads): " << static_cast<double>(best_k) / hardware_threads << "\n";

    report_file << "\nBest K: " << best_k << "\n";
    report_file << "Hardware threads: " << hardware_threads << "\n";
}

int main()
{
    std::ofstream report_file("Report.txt");

    std::vector<size_t> data_sizes = { 100000000, 300000000, 500000000 };

    for (size_t size : data_sizes) 
    {
        auto data = generate_data(size);
        run_experiments(data, report_file);
    }

    std::cout << "\nDone. Check Report.txt\n";
    report_file.close();
    return 0;
}