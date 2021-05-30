#include <iostream>
#include <sstream>
#include <cassert>

#include "My_Parser.hpp"

void test_without_callback()
{
	TokenParser test;
	test.Parse("abc def 123    678    agsj");
	std::cout << "test_without_callback: Done" << std::endl;
}

void test_without_tokens()
{
	std::stringstream output;
	TokenParser test;
	test.SetStartCallback([&output](){output << "Parsing starts: ";});
	test.SetEndCallback([&output](){output << "Parsing ends.";});
	test.SetDigitTokenCallback([&output](const uint64_t token){output << "[D] " << token << " ";});
	test.SetStringTokenCallback([&output](const std::string& token){output << "[S] " << token << " ";});
	test.Parse("  \t  \n \n");
	assert(output.str() == "Parsing starts: Parsing ends.");
	std::cout << "test_without_tokens: Done" << std::endl;
}

void test_with_all()
{
	std::stringstream output;
	TokenParser test;
	test.SetStartCallback([&output](){output << "Parsing starts: ";});
	test.SetEndCallback([&output](){output << "Parsing ends.";});
	test.SetDigitTokenCallback([&output](const uint64_t token){output << "[D] " << token << " ";});
	test.SetStringTokenCallback([&output](const std::string& token){output << "[S] " << token << " ";});
	test.Parse("abc def 123    678    agsj9s");
	assert(output.str() == "Parsing starts: [S] abc [S] def [D] 123 [D] 678 [S] agsj9s Parsing ends.");
	std::cout << "test_with_all: Done" << std::endl;
}

void test_with_only_string_tokens()
{
	std::stringstream output;
	TokenParser test;
	test.SetStartCallback([&output](){output << "Parsing starts: ";});
	test.SetEndCallback([&output](){output << "Parsing ends.";});
	test.SetStringTokenCallback([&output](const std::string& token){output << "[S] " << token << " ";});
	test.Parse("abc def 123    678    agsj9s");
	assert(output.str() == "Parsing starts: [S] abc [S] def [S] agsj9s Parsing ends.");
	std::cout << "test_with_only_string_tokens: Done" << std::endl;
}

void test_with_only_digit_tokens()
{
	std::stringstream output;
	TokenParser test;
	test.SetStartCallback([&output](){output << "Parsing starts: ";});
	test.SetEndCallback([&output](){output << "Parsing ends.";});
	test.SetDigitTokenCallback([&output](const uint64_t token){output << "[D] " << token << " ";});
	test.Parse("abc def 123    678    agsj9s");
	assert(output.str() == "Parsing starts: [D] 123 [D] 678 Parsing ends.");
	std::cout << "test_with_only_digit_tokens: Done" << std::endl;
}

void test_with_no_start()
{
	std::stringstream output;
	TokenParser test;
	test.SetEndCallback([&output](){output << "Parsing ends.";});
	test.SetDigitTokenCallback([&output](const uint64_t token){output << "[D] " << token << " ";});
	test.SetStringTokenCallback([&output](const std::string& token){output << "[S] " << token << " ";});
	test.Parse("abc def 123    678    agsj9s");
	assert(output.str() == "[S] abc [S] def [D] 123 [D] 678 [S] agsj9s Parsing ends.");
	std::cout << "test_with_no_start: Done" << std::endl;
}

void test_with_two_same_callbacks()
{
	std::stringstream output;
	TokenParser test;
	test.SetStartCallback([&output](){output << "Parsing starts: ";});
	test.SetEndCallback([&output](){output << "Parsing ends.";});
	test.SetDigitTokenCallback([&output](const uint64_t token){output << "[D] " << token << " ";});
	test.SetStringTokenCallback([&output](const std::string& token){output << "[S] " << token << " ";});
	test.SetDigitTokenCallback([&output](const uint64_t token){output << "[Digit] " << token << " ";});
	test.Parse("abc def 123    678    agsj9s");
	assert(output.str() == "Parsing starts: [S] abc [S] def [Digit] 123 [Digit] 678 [S] agsj9s Parsing ends.");
	std::cout << "test_with_two_same_callbacks: Done" << std::endl;
}

void test_with_emptystring()
{
	std::stringstream output;
	TokenParser test;
	test.SetStartCallback([&output](){output << "Parsing starts: ";});
	test.SetEndCallback([&output](){output << "Parsing ends.";});
	test.SetDigitTokenCallback([&output](const uint64_t token){output << "[D] " << token << " ";});
	test.SetStringTokenCallback([&output](const std::string& token){output << "[S] " << token << " ";});
	test.Parse("");
	assert(output.str() == "Parsing starts: Parsing ends.");
	std::cout << "test_with_empty_string: Done" << std::endl;
}

void test_with_one_symbol_digit_token()
{
	std::stringstream output;
	TokenParser test;
	test.SetStartCallback([&output](){output << "Parsing starts: ";});
	test.SetEndCallback([&output](){output << "Parsing ends.";});
	test.SetDigitTokenCallback([&output](const uint64_t token){output << "[D] " << token << " ";});
	test.SetStringTokenCallback([&output](const std::string& token){output << "[S] " << token << " ";});
	test.Parse("1");
	assert(output.str() == "Parsing starts: [D] 1 Parsing ends.");
	std::cout << "test_with_one_symbol_digit_token: Done" << std::endl;
}

void test_with_one_symbol_string_token()
{
	std::stringstream output;
	TokenParser test;
	test.SetStartCallback([&output](){output << "Parsing starts: ";});
	test.SetEndCallback([&output](){output << "Parsing ends.";});
	test.SetDigitTokenCallback([&output](const uint64_t token){output << "[D] " << token << " ";});
	test.SetStringTokenCallback([&output](const std::string& token){output << "[S] " << token << " ";});
	test.Parse("a");
	assert(output.str() == "Parsing starts: [S] a Parsing ends.");
	std::cout << "test_with_one_symbol_string_token: Done" << std::endl;
}

void uint64_out_of_range_test()
{
	std::stringstream output;
	TokenParser test;
	test.SetStartCallback([&output](){output << "Parsing starts: ";});
	test.SetEndCallback([&output](){output << "Parsing ends.";});
	test.SetDigitTokenCallback([&output](const uint64_t token){output << "[D] " << token << " ";});
	test.SetStringTokenCallback([&output](const std::string& token){output << "[S] " << token << " ";});
	test.Parse("18446744073709551615    18446744073709551616");
	assert(output.str() == "Parsing starts: [D] 18446744073709551615 [S] 18446744073709551616 Parsing ends.");
	std::cout << "uint64_out_of_range_test: Done" << std::endl;
}

int main()
{
	test_without_callback();
	test_without_tokens();
	test_with_no_start();
	test_with_only_digit_tokens();
	test_with_only_string_tokens();
	test_with_all();
	test_with_two_same_callbacks();
	test_with_emptystring();
	test_with_one_symbol_digit_token();
	test_with_one_symbol_string_token();
	uint64_out_of_range_test();
	return 0;
}
