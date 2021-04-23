#pragma once
#include <istream>
#include <ostream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
private:
    std::ostream& out_;
    static constexpr char Separator = ' ';
    Error process(bool arg);
    Error process(uint64_t arg);
    template <class T>
    Error process(T value);
    template <class T, class... ArgsT>
    Error process(T&&value, ArgsT&&... args);
};

class Deserializer
{
public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
private:
    std::istream& in_;
    Error process(bool &arg);
    Error process(uint64_t &arg);
    template <class T>
    Error process(T& value);
    template <class T, class... ArgsT>
    Error process(T&& value, ArgsT&&... args);
};

#include "serializer.tpp"