#pragma once
#include <iostream>
#include <string>
#include <chrono>

class Timer {
public:
    Timer(const std::string& name, std::ostream& out = std::cout)
        : m_Name(name), m_Out(out), m_StartTime(std::chrono::high_resolution_clock::now()) {
    }

    ~Timer() {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
        m_Out << m_Name << ": " << duration << " ms\n";
    }

private:
    std::string m_Name;
    std::ostream& m_Out;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
};