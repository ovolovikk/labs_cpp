#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <map>

struct Action 
{
    std::string type; 
    int index;
    int value;

    Action(std::string t, int i = 0, int v = 0) : type(t), index(i), value(v) 
    {
    }
};

void generate_action_file(const std::string& filename, 
                          size_t num_actions, 
                          const std::map<std::string, double>& weights) 
{
    std::vector<std::string> keys;
    std::vector<double> probs;

    for (const auto& pair : weights) 
    {
        keys.push_back(pair.first);
        probs.push_back(pair.second);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> dist(probs.begin(), probs.end());

    std::ofstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Could not open file to write: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < num_actions; ++i) 
    {
        std::string op = keys[dist(gen)];

        if (op == "read0") 
        {
            file << "read 0\n";
        } 
        else if (op == "write0") 
        {
            file << "write 0 1\n"; 
        } 
        else if (op == "read1") 
        {
            file << "read 1\n";
        } 
        else if (op == "write1") 
        {
            file << "write 1 1\n";
        } 
        else if (op == "string") 
        {
            file << "string\n";
        }
    }
}