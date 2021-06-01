#pragma once
#include <functional>
#include <vector>
#include <future>
#include <queue>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <condition_variable>

using task = std::function<void ()>;

class ThreadPool
{
    public:
        ~ThreadPool();
        explicit ThreadPool(size_t poolSize);

        template <class Func, class... Args>
        auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;

    private:
        std::atomic<bool> finished;
        std::vector<std::thread> threads;
        std::queue<task> tqueue;
        std::mutex mutex_;
        std::condition_variable cond;
};      

#include "ThreadPool.tpp"