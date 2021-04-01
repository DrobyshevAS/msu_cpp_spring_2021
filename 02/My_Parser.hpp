#pragma once

#include <functional>
#include <string>


using ParseStartFinish = std::function<void()>;
using StringToken = std::function<void(const std::string& token)>;
using DigitToken = std::function<void(uint64_t token)>;

class TokenParser
{


public:
    TokenParser() = default;
    void SetStartCallback(const ParseStartFinish& new_StartCallback);
    void SetEndCallback(const ParseStartFinish& new_EndCallback);
    void SetDigitTokenCallback(const DigitToken& new_DigitTokenCallback);
    void SetStringTokenCallback(const StringToken& new_StringTokenCallback);
    void Parse(const std::string& text);

private: 
    ParseStartFinish StartCallback = [](){};
    ParseStartFinish EndCallback = [](){};
    DigitToken DigitTokenCallback = [](uint64_t token){};
    StringToken StringTokenCallback = [](const std::string& token){};
};