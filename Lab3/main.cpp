#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <sstream>
#include <latch>
#include <barrier>
#include <syncstream>

void f(char setName, int actionIndex)
{
    std::osyncstream sout(std::cout);
    sout << "Action " << actionIndex << " from set " << setName 
         << " executed." << std::endl;
}

void run_actions(char setName, int start, int end)
{
    for (int i = start; i <= end; ++i)
    {
        f(setName, i);
    }
}

int main()
{
    std::osyncstream sout(std::cout);
    sout << "Computation started." << std::endl;

    std::latch latch_a(1), latch_b(1), latch_c(1);
    std::latch latch_d_e(2), latch_f_g(2), latch_h_i(2);
    std::latch latch_all_done(1);

    std::barrier barrier_a(3, [&]() noexcept { latch_a.count_down(); });
    std::barrier barrier_b(3, [&]() noexcept { latch_b.count_down(); });
    std::barrier barrier_c(2, [&]() noexcept { latch_c.count_down(); });

    std::barrier barrier_d(3, [&]() noexcept { latch_d_e.count_down(); });
    std::barrier barrier_e(3, [&]() noexcept { latch_d_e.count_down(); });
    std::barrier barrier_f(2, [&]() noexcept { latch_f_g.count_down(); });
    std::barrier barrier_g(2, [&]() noexcept { latch_f_g.count_down(); });

    std::barrier barrier_h(2, [&]() noexcept { latch_h_i.count_down(); });
    std::barrier barrier_i(5, [&]() noexcept { latch_h_i.count_down(); });

    std::barrier barrier_j(7, [&]() noexcept { latch_all_done.count_down(); });

    auto worker1 = [&]() {
        run_actions('a', 1, 3);
        barrier_a.arrive_and_wait();

        latch_a.wait();
        run_actions('d', 1, 4);
        barrier_d.arrive_and_wait();

        latch_d_e.wait();
        run_actions('h', 1, 2);
        barrier_h.arrive_and_wait();

        latch_h_i.wait();
        run_actions('j', 1, 2);
        barrier_j.arrive_and_wait();
        };

    auto worker2 = [&]() {
        run_actions('a', 4, 6);
        barrier_a.arrive_and_wait();

        latch_a.wait();
        run_actions('d', 5, 8);
        barrier_d.arrive_and_wait();

        latch_d_e.wait();
        run_actions('h', 3, 4);
        barrier_h.arrive_and_wait();

        latch_h_i.wait();
        run_actions('j', 3, 3);
        barrier_j.arrive_and_wait();
        };

    auto worker3 = [&]() {
        run_actions('a', 7, 7);
        barrier_a.arrive_and_wait();
        run_actions('b', 1, 2);
        barrier_b.arrive_and_wait();

        latch_a.wait();
        run_actions('d', 9, 9);
        barrier_d.arrive_and_wait();
        latch_b.wait();
        run_actions('e', 1, 3);
        barrier_e.arrive_and_wait();

        latch_f_g.wait();
        run_actions('i', 1, 2);
        barrier_i.arrive_and_wait();

        latch_h_i.wait();
        run_actions('j', 4, 4);
        barrier_j.arrive_and_wait();
        };

    auto worker4 = [&]() {
        run_actions('b', 3, 5);
        barrier_b.arrive_and_wait();

        latch_b.wait();
        run_actions('e', 4, 7);
        barrier_e.arrive_and_wait();

        latch_f_g.wait();
        run_actions('i', 3, 4);
        barrier_i.arrive_and_wait();

        latch_h_i.wait();
        run_actions('j', 5, 5);
        barrier_j.arrive_and_wait();
        };

    auto worker5 = [&]() {
        run_actions('b', 6, 8);
        barrier_b.arrive_and_wait();

        latch_b.wait();
        run_actions('e', 8, 8);
        barrier_e.arrive_and_wait();
        run_actions('f', 1, 3);
        barrier_f.arrive_and_wait();

        latch_f_g.wait();
        run_actions('i', 5, 6);
        barrier_i.arrive_and_wait();

        latch_h_i.wait();
        run_actions('j', 6, 6);
        barrier_j.arrive_and_wait();
        };

    auto worker6 = [&]() {
        run_actions('c', 1, 4);
        barrier_c.arrive_and_wait();

        latch_b.wait();
        run_actions('f', 4, 6);
        barrier_f.arrive_and_wait();
        latch_c.wait();
        run_actions('g', 1, 1);
        barrier_g.arrive_and_wait();

        latch_f_g.wait();
        run_actions('i', 7, 7);
        barrier_i.arrive_and_wait();

        latch_h_i.wait();
        run_actions('j', 7, 7);
        barrier_j.arrive_and_wait();
        };

    auto worker7 = [&]() {
        run_actions('c', 5, 8);
        barrier_c.arrive_and_wait();

        latch_c.wait();
        run_actions('g', 2, 5);
        barrier_g.arrive_and_wait();

        latch_f_g.wait();
        run_actions('i', 8, 8);
        barrier_i.arrive_and_wait();

        latch_h_i.wait();
        run_actions('j', 8, 8);
        barrier_j.arrive_and_wait();
        };

    std::vector<std::jthread> threads;
    threads.emplace_back(worker1);
    threads.emplace_back(worker2);
    threads.emplace_back(worker3);
    threads.emplace_back(worker4);
    threads.emplace_back(worker5);
    threads.emplace_back(worker6);
    threads.emplace_back(worker7);

    latch_all_done.wait();

    sout << "Computation finished." << std::endl;

    return 0;
}