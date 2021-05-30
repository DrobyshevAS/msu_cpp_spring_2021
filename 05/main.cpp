#include <cassert>
#include <string.h>
#include <iostream>
#include <sstream>
#include "serializer.hpp"

struct CorrectData_one_uint
{
    uint64_t a;
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a);
    }
};

struct CorrectData_one_bool
{
    bool a;
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a);
    }
};

struct CorrectData
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

struct UncorrectData1
{
    uint64_t a;
    bool b;
    std::string c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

struct UncorrectData2
{
    uint64_t a;
    std::string b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

struct CorruptedData {
    uint64_t a;
    bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a, b);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer) {
        return deserializer(a, b);
    }
};

void test1()
{
    CorrectData x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    CorrectData y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);

    std::cout << "Test 1: Done." << std::endl;
};

void test2()
{
    UncorrectData1 x { 1, true, "name"};

    std::stringstream stream;

    Serializer serializer(stream);
    assert(serializer.save(x) == Error::CorruptedArchive);

    std::cout << "Test 2: Done." << std::endl;
};

void test3()
{
    CorrectData x { 1, true, 2};

    std::stringstream stream;

    Serializer serializer(stream);
    assert(serializer.save(x) == Error::NoError);

    UncorrectData2 y { 1, "name", 2};

    Deserializer deserializer(stream);
    assert(deserializer.load(y) == Error::CorruptedArchive);

    std::cout << "Test 3: Done." << std::endl;
};

void test_only_uint()
{
    CorrectData_one_uint x {1};
    std::stringstream stream;
    Serializer serializer(stream);
    assert(serializer.save(x) == Error::NoError);

    CorrectData_one_uint y;
    Deserializer deserializer(stream);
    assert(deserializer.load(y) == Error::NoError);

    assert(x.a = y.a);
    std::cout << "test only uint: Done." << std::endl;
};

void test_only_bool()
{
    CorrectData_one_bool x {true};
    std::stringstream stream;
    Serializer serializer(stream);
    assert(serializer.save(x) == Error::NoError);

    CorrectData_one_bool y;
    Deserializer deserializer(stream);
    assert(deserializer.load(y) == Error::NoError);

    assert(x.a = y.a);
    std::cout << "test only bool: Done." << std::endl;
};

void too_many_arguments_test()
{
    std::stringstream stream;
    CorrectData y;
    stream << "2 false 3 4";
    Deserializer deserializer(stream);
    assert(deserializer.load(y) == Error::TooManyArguments);
    std::cout << "too many arguments test: Done." << std::endl;
};

void not_enough_arguments_test()
{
    std::stringstream stream;
    CorrectData y;
    stream << "2 false";
    Deserializer deserializer(stream);
    assert(deserializer.load(y) == Error::NotEnoughArguments);
    std::cout << "not enough arguments test: Done." << std::endl;
};

void not_valid_test()
{
    std::stringstream stream;
    stream << "18446744073709551617 true";
    CorruptedData y;
    Deserializer deserializer0(stream);
    assert(deserializer0.load(y) == Error::CorruptedArchive);

    stream.clear();
    stream << "1 True";
    Deserializer deserializer1(stream);
    assert(deserializer1.load(y) == Error::CorruptedArchive);

    stream.clear();
    stream << "1 1";
    Deserializer deserializer2(stream);
    assert(deserializer2.load(y) == Error::CorruptedArchive);

    stream.clear();
    stream << "1 0";
    Deserializer deserializer3(stream);
    assert(deserializer3.load(y) == Error::CorruptedArchive);

    stream.clear();
    stream << "juststring true";
    Deserializer deserializer4(stream);
    assert(deserializer4.load(y) == Error::CorruptedArchive);
    std::cout << "not valid test: Done." << std::endl;
}

int main()
{
    test1();
    test2();
    test3();
    test_only_uint();
    test_only_bool();
    too_many_arguments_test();
    not_enough_arguments_test();
    not_valid_test();
    return 0;
}

