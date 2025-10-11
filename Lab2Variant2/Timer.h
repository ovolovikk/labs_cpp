#pragma once
#include <iostream>
#include <string>
#include <chrono>

class Timer {
public:
    Timer(const std::string& name)
        : m_Name(name), m_StartTime(std::chrono::high_resolution_clock::now()) {
    }

    ~Timer() {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
        std::cout << m_Name << ": " << duration << " ms\n";
    }

private:
    std::string m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
};