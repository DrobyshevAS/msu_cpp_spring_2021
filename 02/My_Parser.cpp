#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "My_Parser.hpp"

void TokenParser::SetStartCallback(const ParseStartFinish& new_StartCallback)
{
	StartCallback = new_StartCallback;
}
void TokenParser::SetDigitTokenCallback(const DigitToken& new_DigitTokenCallback)
{
	DigitTokenCallback = new_DigitTokenCallback;
}
void TokenParser::SetStringTokenCallback(const StringToken& new_StringTokenCallback) 
{
	StringTokenCallback = new_StringTokenCallback;
}
void TokenParser::SetEndCallback(const ParseStartFinish& new_EndCallback) 
{
	EndCallback = new_EndCallback;
}

void TokenParser::Parse(const std::string& text)
{
	StartCallback();
	std::stringstream ss(text);
	std::string token;	
	while (ss >> token)
	{	
		int i = 0;
		int flag = 1;
		while (i < token.length())
		{
			if (!isdigit(token[i]))
			{
				flag = 0;
				StringTokenCallback(token);
				break;
			}
			i++;
		}
		if (flag == 1)
		{
			try 
			{
				DigitTokenCallback(stoull(token));
			}
			catch (std::out_of_range &) 
			{
				StringTokenCallback(token);
			}
		}
	}
	EndCallback();
}
