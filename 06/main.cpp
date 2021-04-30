#include <cassert>
#include "format.hpp"

void test_with_correct_data()
{
    std::string text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
    std::cout << "test with correct data: Done" << std::endl;
}

void test_with_two_open_barckets()
{
    try
    {
        format("{{1}+{1} = {0}", 2, "one");
    }
    catch (const std::runtime_error &error)
    {
        assert(error.what() == std::string("Two consecutive parentheses {"));
    }
    std::cout << "test with two open barckets: Done" << std::endl;
}

void test_without_open_bracket()
{
    try
    {
        format("}{1}+{1} = {0}", 2, "one");
    }
    catch (const std::runtime_error &error)
    {
        assert(error.what() == std::string("} bracket without { bracket"));
    }
    std::cout << "test without open bracket: Done" << std::endl;
}

void test_without_data_between_brackets()
{
    try
    {
        format("{1}+{} = {0}", 2, "one");
    }
    catch (const std::runtime_error &error)
    {
        assert(error.what() == std::string("No data between brackets{}"));
    }
    std::cout << "test without data between brackets: Done" << std::endl;
}

void test_with_incorrect_data_between_brackets()
{
    try
    {
        format("{1}+{23a4} = {0}", 2, "one");
    }
    catch (const std::runtime_error &error)
    {
        assert(error.what() == std::string("Incorrect data between brackets{}"));
    }
    std::cout << "test with incorrect data between brackets: Done" << std::endl;
}

void test_with_not_enough_args()
{
    try
    {
        format("{1}+{4} = {0}", 2, "one");
    }
    catch (const std::runtime_error &error)
    {
        assert(error.what() == std::string("Too few arguments"));
    }
    std::cout << "test with not enough arguments: Done" << std::endl;
}

void test_with_empty_string()
{
    std::string text = format("", 2, "one");
    assert(text == "");
    std::cout << "test with empty string: Done" << std::endl;
}

void test_without_brackets()
{
    std::string text = format("No pain no gain", 2, "one");
    assert(text == "No pain no gain");
    std::cout << "test without brackets: Done" << std::endl;
}

int main()
{
    test_with_correct_data();
    test_with_two_open_barckets();
    test_without_open_bracket();
    test_without_data_between_brackets();
    test_with_incorrect_data_between_brackets();
    test_with_not_enough_args();
    test_with_empty_string();
    test_without_brackets();
    return 0;
}