ThreadPool::~ThreadPool()
{
    finished = true;
    cond.notify_all();
    for (auto& thread: threads)
    {
        thread.join();
    }
}

ThreadPool::ThreadPool(size_t poolSize)
{
    finished = false;
    for (size_t i = 0; i < poolSize; i++)
    {
        threads.emplace_back([this]() {
            while(not finished)
            {   
                {
                    std::unique_lock<std::mutex> lock(mutex_);
                    while (tqueue.empty() && not finished)
                    {
                        cond.wait(lock);
                    }
                }
                mutex_.lock();
                if (!tqueue.empty())
                {
                    auto next_task = std::move(tqueue.front());
                    tqueue.pop();
                    mutex_.unlock();
                    next_task();
                }
                else
                {
                    mutex_.unlock();
                    continue;
                }
            }
        });
    }
}

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))>
{
    auto new_task = std::make_shared<std::packaged_task<decltype(func(args...))()>>([func, args...]() {return func(args...);});

    std::future<decltype(func(args...))> res = new_task->get_future();
    {
        std::unique_lock<std::mutex> lock(mutex_);
        tqueue.emplace([new_task]() { (*new_task)(); });
    }
    cond.notify_one();
    return res;
}