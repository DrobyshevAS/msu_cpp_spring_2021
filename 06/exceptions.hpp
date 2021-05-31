#pragma once

#include <sstream>
#include <stdexcept>
#include <string>

class BaseError : public std::logic_error 
{
    public:
        BaseError(const std::string& error_log) : std::logic_error(error_log) 
        {
            std::ostringstream error_stream;
            error_stream  << error_log;
            err_ = error_stream.str();
        }

        const char* what() const throw() override 
        {
            return err_.c_str();
        }

    private:
        std::string err_;
};

class TooManyArgumentsError : public BaseError 
{
    public:
        TooManyArgumentsError(const std::string& error_log) : BaseError(error_log) {}
};

class NotEnoughArgumentsError : public BaseError 
{
    public:
        NotEnoughArgumentsError(const std::string& error_log) : BaseError(error_log) {}
};

class IncorrectDataBetweenBrackets : public BaseError 
{
    public:
        IncorrectDataBetweenBrackets(const std::string& error_log) : BaseError(error_log) {}
};

class BracketError : public BaseError 
{
    public:
        BracketError(const std::string& error_log) : BaseError(error_log) {}
};