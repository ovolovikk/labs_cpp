# 🧪 C++ Laboratory Works

![Language](https://img.shields.io/badge/language-C++-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Status](https://img.shields.io/badge/status-Active-brightgreen.svg)

## 📖 Overview

Welcome to my **C++ Labs** repository. This collection contains source code and documentation for laboratory works completed as part of the **Advanced C++** course.

The main goal of this repository is to demonstrate understanding of advanced multithreading C++.

## 📂 Repository Structure

The repository is organized by laboratory work. Each folder contains the source code, headers, and relevant input/output files.

| Folder | Topic | Description |
| :--- | :--- | :--- |
| `/Lab1` | **Statistical Simulation & CLI** | Implementation of a statistical experiment (Monte Carlo method) to calculate properties of a system. Features command-line argument parsing and data export to CSV. |
| `/Lab2` | **Parallel Algorithms & Performance** | A performance comparison between `std::any_of` with sequential/parallel policies and a custom parallel implementation. Explores optimal thread count for a given task. |
| `/Lab3` | **Synchronization with Latches & Barriers** | Implements a concurrent computation based on a dependency graph. Uses C++20 synchronization primitives (`std::jthread`, `std::latch`, `std::barrier`) to manage a hardcoded task distribution among worker threads, ensuring correct execution order according to the graph's dependencies. |
| `/Lab4` | **Multithreading & File I/O** | A program that simulates concurrent operations on shared resources, along with a weighted test case generator. |
| `/Lab5` | **Asynchronous Programming with Futures** | A demonstration of task-based parallelism using `std::async` and `std::future` to manage concurrent computations and their results. |
| `/Lab6` | **Concurrency & Synchronization** | A classic producer-consumer problem demonstrating the use of `std::thread`, `std::mutex`, and `std::condition_variable` for thread synchronization. |
| ... | ... | ... |

## 🛠️ Technologies & Tools

* **Language**: C++ (Standard: C++20)
* **Compiler**: MSVC
* **Build System**: CMake / Visual Studio Solution
* **IDE**: Visual Studio 2026

## 🚀 How to Build and Run

Ensure you have a C++ compiler installed (e.g., `g++` or MSVC) and CMake.
```bash
# Clone the repository
git clone https://github.com/ovolovikk/labs_cpp
cd labs_cpp

# Create build directory
mkdir build && cd build

# Configure and Build
cmake ..
cmake --build .