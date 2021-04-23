#include <cassert>
#include <string.h>
#include <iostream>
#include <sstream>
#include "serializer.hpp"


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

int main()
{
    test1();
    test2();
    test3();
    return 0;
}

