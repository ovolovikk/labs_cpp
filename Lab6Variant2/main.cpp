#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::queue<int> numbers;
std::mutex mtx;
std::condition_variable cv; // signals thread to wake up and gen next variable
bool paused = true;
bool finished = false;

void randomNumberGenerator() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 256);

    for (int i = 0; i < 10; ++i) 
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return !paused; });
        }

        if (finished) break;

        int random_number = distrib(gen);

        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "Generated " << random_number << ".\n";
            numbers.push(random_number);

            if (random_number % 2 != 0) {
                std::cout << "  -> Pausing thread (generated odd number: " << random_number << ").\n";
            }

            paused = true;
        }
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
        paused = false;
        cv.notify_one();
    }
}

void print_queue() 
{
    std::lock_guard<std::mutex> lock(mtx);
    std::queue<int> temp = numbers;
    std::cout << "Current queue: [ ";
    while (!temp.empty()) 
    {
        std::cout << temp.front() << " ";
        temp.pop();
    }
    std::cout << "]\n\n";
}

int main() 
{
    std::thread generator_thread(randomNumberGenerator);

    std::cout << "Starting thread execution. Type 'next' to resume or 'exit' to quit.\n\n";

    std::string command;
    while (true) 
    {
        print_queue();

        {
            std::lock_guard<std::mutex> lock(mtx);
            if (finished) 
            {
                std::cout << "Generator thread has finished execution.\n";
                break;
            }
        }

        std::cout << "Awaiting command: ";
        std::cin >> command;

        if (command == "next") 
        {
            {
                std::lock_guard<std::mutex> lock(mtx);
                paused = false;
            }
            cv.notify_one();
        }
        else if (command == "exit") 
        {
            {
                std::lock_guard<std::mutex> lock(mtx);
                finished = true;
                paused = false;
            }
            cv.notify_one();
            break;
        }
        else 
        {
            std::cout << "Unknown command.\n";
        }
    }

    if (generator_thread.joinable())
    {
        generator_thread.join();
    }

    return 0;
}