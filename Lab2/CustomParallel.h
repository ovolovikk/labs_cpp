#pragma once
#include <vector>
#include <thread>
#include <atomic>
#include <iterator>
#include <algorithm>

template<typename ForwardIt, typename Predicate>
bool custom_parallel_any_of(ForwardIt first, ForwardIt last, Predicate p, unsigned int K) 
{
    if (K == 0) return false;
    if (K == 1) 
    {
        return std::any_of(first, last, p);
    }

    const auto total_size = std::distance(first, last);
    if (total_size == 0) return false;

    const auto chunk_size = total_size / K;
    std::vector<std::jthread> threads;
    threads.reserve(K);

    std::atomic<bool> found(false);

    auto worker = [&](ForwardIt chunk_first, ForwardIt chunk_last) 
        {
        if (found.load(std::memory_order_acquire))
        {
            return;
        }
        if (std::any_of(chunk_first, chunk_last, p))
        {
            found.store(true, std::memory_order_release);
        }
        };

    ForwardIt current_start = first;
    for (unsigned int i = 0; i < K; ++i) 
    {
        if (i == K - 1) 
        {
            threads.emplace_back(worker, current_start, last);
        }
        else 
        {
            ForwardIt current_end = std::next(current_start, chunk_size);
            threads.emplace_back(worker, current_start, current_end);
            current_start = current_end;
        }
    }

    return found.load();
}