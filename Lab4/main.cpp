#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>

#include "ThreadData.h"
#include "Generator.h"

const size_t NUM_ACTIONS_PER_FILE = 200000;
const int AVG_RUNS = 3;

std::vector<Action> load_actions(const std::string& filename)
{
    std::vector<Action> actions;
    std::ifstream file(filename);
    std::string line;
    std::string type;
    int index, value;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        ss >> type;
        if (type == "read")
        {
            ss >> index;
            actions.emplace_back(type, index);
        } else if (type == "write")
        {
            ss >> index >> value;
            actions.emplace_back(type, index, value);
        } else if (type == "string")
        {
            actions.emplace_back(type);
        }
    }
    return actions;
}

void worker(ThreadData* data, const std::vector<Action>* actions) 
{
    for (const auto& action : *actions)
    {
        if (action.type == "read")
        {
            // volatile to disable optimization of compiler
            volatile int val = data->read(action.index);
        } else if (action.type == "write")
        {
            data->write(action.index, action.value);
        } else if (action.type == "string")
        {
            volatile std::string s = data->to_string();
        }
    }
}

double run_test(const std::vector<std::string>& filenames)
{
    ThreadData data;
    std::vector<std::vector<Action>> all_actions;
    all_actions.reserve(filenames.size());

    for (const auto& f : filenames) {
        all_actions.push_back(load_actions(f));
    }

    std::vector<std::thread> threads;
    threads.reserve(filenames.size());

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < filenames.size(); ++i) {
        threads.emplace_back(worker, &data, &all_actions[i]);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;
    return ms.count();
}

double average_test(const std::vector<std::string>& filenames) {
    double total_ms = 0;
    for (int i = 0; i < AVG_RUNS; ++i) {
        total_ms += run_test(filenames);
    }
    return total_ms / AVG_RUNS;
}

int main() {
    std::cout << "Generating action files (N=" << NUM_ACTIONS_PER_FILE << ")...\n";

    std::map<std::string, double> weightsA = {
        {"read0", 0.40}, {"write0", 0.05},
        {"read1", 0.05}, {"write1", 0.05},
        {"string", 0.45}
    };
    generate_action_file("actionsA_1.txt", NUM_ACTIONS_PER_FILE, weightsA);
    generate_action_file("actionsA_2.txt", NUM_ACTIONS_PER_FILE, weightsA);
    generate_action_file("actionsA_3.txt", NUM_ACTIONS_PER_FILE, weightsA);

    std::map<std::string, double> weightsB = {
        {"read0", 0.20}, {"write0", 0.20},
        {"read1", 0.20}, {"write1", 0.20},
        {"string", 0.20}
    };
    generate_action_file("actionsB_1.txt", NUM_ACTIONS_PER_FILE, weightsB);
    generate_action_file("actionsB_2.txt", NUM_ACTIONS_PER_FILE, weightsB);
    generate_action_file("actionsB_3.txt", NUM_ACTIONS_PER_FILE, weightsB);

    std::map<std::string, double> weightsC = {
        {"read0", 0.05}, {"write0", 0.05},
        {"read1", 0.40}, {"write1", 0.45},
        {"string", 0.05}                  
    };
    generate_action_file("actionsC_1.txt", NUM_ACTIONS_PER_FILE, weightsC);
    generate_action_file("actionsC_2.txt", NUM_ACTIONS_PER_FILE, weightsC);
    generate_action_file("actionsC_3.txt", NUM_ACTIONS_PER_FILE, weightsC);

    std::cout << "File generation complete.\n\n";
    std::cout << "Running benchmarks (averaging " << AVG_RUNS << " runs)...\n" << std::endl;

    double resA1 = average_test({"actionsA_1.txt"});
    double resA2 = average_test({"actionsA_1.txt", "actionsA_2.txt"});
    double resA3 = average_test({"actionsA_1.txt", "actionsA_2.txt", "actionsA_3.txt"});

    double resB1 = average_test({"actionsB_1.txt"});
    double resB2 = average_test({"actionsB_1.txt", "actionsB_2.txt"});
    double resB3 = average_test({"actionsB_1.txt", "actionsB_2.txt", "actionsB_3.txt"});

    double resC1 = average_test({"actionsC_1.txt"});
    double resC2 = average_test({"actionsC_1.txt", "actionsC_2.txt"});
    double resC3 = average_test({"actionsC_1.txt", "actionsC_2.txt", "actionsC_3.txt"});

    std::cout << "========== ТАБЛИЦЯ РЕЗУЛЬТАТІВ (усереднені, мс) ==========\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "| " << std::setw(15) << "Сценарій"
              << " | " << std::setw(10) << "1 Потік"
              << " | " << std::setw(10) << "2 Потоки"
              << " | " << std::setw(10) << "3 Потоки" << " |\n";
    std::cout << "|-----------------|------------|------------|------------|\n";
    
    std::cout << "| " << std::setw(15) << "Оптимізований (A)"
              << " | " << std::setw(8) << resA1
              << " | " << std::setw(10) << resA2
              << " | " << std::setw(10) << resA3 << " |\n";

    std::cout << "| " << std::setw(15) << "Рівномірний   (B)"
              << " | " << std::setw(8) << resB1
              << " | " << std::setw(10) << resB2
              << " | " << std::setw(10) << resB3 << " |\n";

    std::cout << "| " << std::setw(15) << "Невідповідний (C)"
              << " | " << std::setw(8) << resC1
              << " | " << std::setw(10) << resC2
              << " | " << std::setw(10) << resC3 << " |\n";
    std::cout << "==========================================================" << std::endl;

    return 0;
}