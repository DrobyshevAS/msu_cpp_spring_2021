#pragma once
#include <cmath>
#include <iostream>

class BigInt {
    public:
        BigInt() = default;
        BigInt(size_t);
        BigInt(const std::string&);
        BigInt(int32_t);
        BigInt(const BigInt&);
        BigInt(BigInt&&);
        ~BigInt();
        BigInt& operator=(const BigInt&);
        BigInt& operator=(BigInt&&);
        BigInt operator+(const BigInt&) const;
        BigInt operator+(int32_t) const;
        BigInt operator-(const BigInt&) const;
        BigInt operator-(int32_t) const;
        BigInt operator-() const;
        BigInt operator*(const BigInt&) const;
        BigInt operator*(int32_t) const;
        bool operator==(const BigInt&) const;
        bool operator!=(const BigInt&) const;
        bool operator>(const BigInt&) const;
        bool operator>=(const BigInt&) const;
        bool operator<(const BigInt&) const;
        bool operator<=(const BigInt&) const;
        friend std::ostream& operator<<(std::ostream& out, const BigInt&);

    private:
        size_t size = 0;
        int32_t* data = nullptr;
        int sign = 1;
        const size_t max_power = 4;
        const int32_t base = static_cast<int32_t>(pow(10, max_power));
};