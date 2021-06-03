#include <cassert>
#include <iostream>
#include <sstream>

#include "BigInt.hpp"

void ostream_test()
{
    std::ostringstream output;
    BigInt a("-18446744073709551617");
    output << a;
    assert(output.str() == std::string("-18446744073709551617"));
    std::cout << "ostream test: Done" << std::endl;
}

void plus_operator_test()
{
    std::ostringstream output;
    BigInt x("18446744073709551617");
    BigInt y("18446744073709551617");
    BigInt z("-18446744073709551617");
    output << x + y << " " << x + z << " " << x + 12;
    assert(output.str() == std::string("36893488147419103234 0 18446744073709551629"));
    std::cout << "operator + test: Done" << std::endl;
}

void minus_operator_test()
{
    std::ostringstream output;
    BigInt x("18446744073709551617");
    BigInt y("18446744073709551617");
    BigInt z("-18446744073709551617");
    BigInt q(12);
    output << x - y << " " << x - z << " " << x - q << " " << -x;
    assert(output.str() == std::string("0 36893488147419103234 18446744073709551605 -18446744073709551617"));
    std::cout << "operator - test: Done" << std::endl;
}

void multiplication_operator_test()
{
    std::ostringstream output;
    BigInt x("18446744073709551617");
    BigInt y("18446744073709551617");
    BigInt z("-18446744073709551617");
    BigInt q = 0;
    output << x * y << " " << x * z << " " << x * q << " " << z * q;
    assert(output.str() == std::string("340282366920938463500268095579187314689 -340282366920938463500268095579187314689 0 0"));
    std::cout << "operator * test: Done" << std::endl;
}

void equal_not_equal_test()
{
    std::ostringstream output;
    BigInt x("18446744073709551617");
    BigInt y("10");
    BigInt z("18446744073709551617");
    assert((x != y) && (x == z));
    std::cout << "equal/not_equal operator test: Done" << std::endl;
}

void more_less_test()
{
    std::ostringstream output;
    BigInt x("18446744073709551617");
    BigInt y("10");
    BigInt z("-18446744073709551617");
    BigInt q("18446744073709551617");
    BigInt r("-10");
    assert((x > y) && (z < q) && (x >= q) && (x > z) && (z < x) && (q <= x) && (y < x));
    std::cout << "more/less operators test: Done" << std::endl;
}

int main()
{
    ostream_test();
    plus_operator_test();
    minus_operator_test();
    multiplication_operator_test();
    equal_not_equal_test();
    more_less_test();
    return 0;
}