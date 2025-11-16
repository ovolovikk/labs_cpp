#pragma once

#include <string>
#include <sstream>
#include <mutex>

class ThreadData 
{
public:
    ThreadData() : field0(0), field1(0) 
    {
    }

    void write(size_t index, int value) 
    {
        if (index == 0) 
        {
            std::lock_guard<std::mutex> lock(mtx_field0);
            field0 = value;
        } 
        else if (index == 1) 
        {
            std::lock_guard<std::mutex> lock(mtx_field1);
            field1 = value;
        }
    }

    int read(size_t index) const 
    {
        if (index == 0) 
        {
            std::lock_guard<std::mutex> lock(mtx_field0);
            return field0;
        } 
        else if (index == 1) 
        {
            std::lock_guard<std::mutex> lock(mtx_field1);
            return field1;
        }
        return -1; 
    }

    operator std::string() const 
    {
        std::lock_guard<std::mutex> lock0(mtx_field0);
        std::lock_guard<std::mutex> lock1(mtx_field1);

        std::stringstream ss;
        ss << "Field0: " << field0 << ", Field1: " << field1;
        return ss.str();
    }

    std::string to_string() const 
    {
        return static_cast<std::string>(*this);
    }

private:
    int field0;
    int field1;

    mutable std::mutex mtx_field0;
    mutable std::mutex mtx_field1;
};