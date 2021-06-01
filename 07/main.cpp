#include <iostream>
#include <cassert>
#include <string>

#include "vector.hpp"

void test_size_capacity()
{
    vector<int> num;
    num.push_back(1);
    num.push_back(2);
    num.push_back(3);
    num.push_back(4);
    num.push_back(5);
    assert(num.size() == 5);
    assert(num.capacity() == 7);
    std::cout << "Test size/capacity: Done"<< std::endl;
}

void test_brackets()
{
    vector<int> num;
    num.push_back(1);
    num.push_back(2);
    num.push_back(3);
    num.push_back(4);
    num.push_back(5);
    num[2] = 5;
    assert(num[0] == 1);
    assert(num[1] == 2);
    assert(num[2] == 5);
    assert(num[3] == 4);
    assert(num[4] == 5);
    try
    {
        num[7] =6;
    }
    catch (std::out_of_range&e)
    {
        assert(e.what() == std::string ("Index out of range"));
    }
    std::cout << "Test brackets: Done"<< std::endl;
}

void test_resize_without_value()
{
    vector<int> num;
    num.resize(5);
    assert(num.size() == 5);
    for (size_t i=0; i<num.size(); i++)
    {
        assert(num[i] == 0);
    }
    std::cout << "Test resize without value: Done"<< std::endl;
}

void test_resize_with_value()
{
    std::cout << "Test resize without value: Starts"<< std::endl;
    vector<int> num;
    num.resize(5,5);
    assert(num.size() == 5);
    for (size_t i=0; i<num.size(); i++)
    {
        assert(num[i] == 5);
    }
    std::cout << "Test resize with value: Done"<< std::endl;
}

void test_begin_end()
{
    vector<int> num;
    num.push_back(1);
    num.push_back(2);
    num.push_back(3);
    num.push_back(4);
    num.push_back(5);
    auto iter = num.begin();
    assert(iter != num.end());
    int i=1;
    for (iter = num.begin(); iter < num.end(); ++iter)
    {
        assert(*iter == i);
        i++;
    }
    std::cout << "Test begin/end: Done"<< std::endl;
}


void test_reversed_begin_end()
{
    vector<int> num;
    num.push_back(1);
    num.push_back(2);
    num.push_back(3);
    num.push_back(4);
    num.push_back(5);
    auto iter = num.rbegin();
    assert(iter != num.rend());
    int i=5;
    for (iter = num.rbegin(); iter > num.rend(); ++iter)
    {
        assert(*iter == i);
        i--;
    }
    std::cout << "Test reversed begin/end: Done"<< std::endl;
}


void iterator_test()
{
    vector<int> num;
    for (size_t i = 0; i < 5; i++)
    {
        num.push_back(i);
    }
    assert(num.begin() == num.rend()--);
    assert(num.rbegin()-- == num.end());
    size_t i = 0;
    for (auto elem: num)
    {
        assert(elem == num[i]);
        i++;
    }
    std::cout << "iterator_test: Done"<< std::endl;
    num.clear();
}

void empty_vector_test()
{
    vector<int> num;
    assert(num.size() == 0);
    assert(num.capacity() == 0);
    assert(num.begin() == num.end());
    assert(num.rbegin() == num.rend());
    try
    {
        auto xyz = num[0];
        assert(xyz == num[0]);
    }
    catch(const std::exception& e)
    {
        assert(e.what() == std::string("Index out of range"));
    }
    std::cout << "empty_vector_test: Done"<< std::endl;
}

void test_push_back_pop_back()
{
    vector<int> num;
    assert(num.size() == 0);
    for (size_t i = 0; i < 5; i++)
    {
        num.push_back(i);
    }
    assert(num.size() == 5);
    for (size_t i = 0; i < 3; i++)
    {
        num.pop_back();
    }
    assert(num.size() == 2);
    std::cout << "test push_back / pop_back: Done"<< std::endl;
}

struct Data 
{
    int a_;
    int b_;
    Data() = default;
    Data(int a, int b) : a_(a), b_(b){}
};

void test_emplace_back()
{
    vector<Data> data_vector;
    data_vector.emplace_back(1, 2);
    data_vector.emplace_back(3, 4);
    
    Data x = data_vector[0];
    Data y = data_vector[1];

    assert((x.a_ == 1) && (x.b_ == 2));
    assert((y.a_ == 3) && (y.b_ == 4));

    std::cout << "test emplace_back: Done"<< std::endl;
}

void empty_clear_test()
{
    vector<int> num;
    assert(num.empty());

    num.push_back(3);
    assert(!num.empty());

    num.clear();
    assert(num.empty());

    std::cout << "test empty/clear: Done"<< std::endl; 
}

void reserve_test()
{
    vector<int> num;

    for (size_t i=0; i < 5; i++)
    {
        num.push_back(3);
    }

    auto cap = num.capacity();

    num.reserve(cap+5);
    assert(num.capacity() == cap+5);

    std::cout << "reserve test: Done"<< std::endl; 
}


int main()
{
    test_size_capacity();
    test_brackets();
    test_resize_without_value();
    test_resize_with_value();
    test_begin_end();
    test_reversed_begin_end();
    iterator_test();
    empty_vector_test();
    test_push_back_pop_back();
    test_emplace_back();
    empty_clear_test();
    reserve_test();
}
