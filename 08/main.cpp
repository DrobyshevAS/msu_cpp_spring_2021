#include <iostream>
#include <sstream>
#include <cassert>
#include "ThreadPool.hpp"

void test_with_one_process()
{
    ThreadPool pool(1);
    auto foo = [](int x) { return x*x; };
    auto task = pool.exec(foo, 5);
    assert(task.get() == 25);
    std::cout << "test with one process : Done" << std::endl;
}

void test_with_few_processes()
{
    ThreadPool pool(8);
    auto foo = [](int x) { return x*x; };
    std::ostringstream output;
    for (int i=0; i<11; i++)
    {
        auto task = pool.exec(foo, i);
        output << task.get() << " ";
    }
    assert(output.str() == std::string("0 1 4 9 16 25 36 49 64 81 100 "));
    std::cout << "test with few processes : Done" << std::endl;
}

int main()
{
    test_with_one_process();
    test_with_few_processes();
}