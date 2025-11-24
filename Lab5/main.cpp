#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include <vector>
#include <mutex>

#define QUICK_DURATION 1
#define SLOW_DURATION 7

std::mutex cout_mutex;

// тут міг бути osyncstream, але з якихось незрозумілих причин з ним не працювало
void computation(const std::string& name, int duration_s) {
    std::this_thread::sleep_for(std::chrono::seconds(duration_s));
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << name << " is done" << std::endl;
}

void work() {
    auto start_time = std::chrono::high_resolution_clock::now();

    auto future_b = std::async(std::launch::async, computation, "B", SLOW_DURATION);
    auto future_c = std::async(std::launch::async, computation, "C", SLOW_DURATION);
    
    auto future_d2_f2 = std::async(std::launch::async, [&]() {
        computation("D2", SLOW_DURATION);
        computation("F2", QUICK_DURATION);
    });

    computation("A", QUICK_DURATION);

    future_b.get();
    future_c.get();

    computation("D1", QUICK_DURATION);

    future_d2_f2.get();

    computation("F1", QUICK_DURATION);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "\nWork is done!" << std::endl;
    std::cout << "Total execution time: " << elapsed.count() << " seconds" << std::endl;
}

int main() {
    work();
    return 0;
}