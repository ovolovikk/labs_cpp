#include <iostream>
#include <coroutine>
#include <queue>
#include <random>
#include <string>

struct task 
{
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    handle_type coro_handle;

    explicit task(handle_type h) : coro_handle(h) {}
    ~task() { if (coro_handle) coro_handle.destroy(); }

    task(const task&) = delete;
    task& operator=(const task&) = delete;
    task(task&& other) noexcept : coro_handle(other.coro_handle) { other.coro_handle = nullptr; }
    task& operator=(task&& other) noexcept {
        if (this != &other) {
            if (coro_handle) coro_handle.destroy();
            coro_handle = other.coro_handle;
            other.coro_handle = nullptr;
        }
        return *this;
    }

    void resume() const { if (coro_handle && !coro_handle.done()) coro_handle.resume(); }

    struct promise_type 
    {
        auto get_return_object() { return task{ handle_type::from_promise(*this) }; }
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }

        auto await_transform(int number) 
        {
            struct odd_suspender : std::suspend_always
            {
                int num;
                bool await_ready() const noexcept { return (num % 2) == 0; }
            };
            return odd_suspender{ {}, number };
        }
    };
};

task randomNumberGenerator(std::queue<int>& numbers)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 256);

    for (int i = 0; i < 10; ++i)
    {
        int random_number = distrib(gen);
        numbers.push(random_number);

        if (random_number % 2 != 0) {
            std::cout << "Generated " << random_number << " (odd) -> Suspending.\n";
        }
        else {
            std::cout << "Generated " << random_number << " (even) -> Continuing.\n";
        }

        co_await random_number;
    }
}

void print_queue(const std::queue<int>& q)
{
    std::queue<int> temp = q;
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
    std::queue<int> numbers;
    task generator = randomNumberGenerator(numbers);

    std::cout << "Starting coroutine. Type 'next' to resume or 'exit' to quit.\n\n";

    generator.resume();

    std::string command;
    while (true)
    {
        print_queue(numbers);

        if (generator.coro_handle.done()) {
            std::cout << "Coroutine has finished.\n";
            break;
        }

        std::cout << "Awaiting command: ";
        std::cin >> command;

        if (command == "next") {
            generator.resume();
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}