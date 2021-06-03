#include "BigInt.hpp"

BigInt::BigInt(size_t size_)
{
    size = size_;
    data = new int32_t[size];
}

BigInt::BigInt(const std::string& number)
{
    std::string number_copy = number;
    if (number_copy.length() != 0)
    {
        if (number_copy[0] == '-') {
            sign = 0;
            number_copy = number_copy.substr(1, number_copy.length());
        }
        size = static_cast<size_t>(number_copy.length() / max_power);
        if (number_copy.length() % max_power != 0)
            size++;
        data = new int32_t[size];
        for (size_t i = 0; i < size - 1; i++) {
            std::string temp = number_copy.substr(number_copy.length() - max_power * (i + 1), max_power);
            data[i] = std::stoi(temp);
        }
        data[size - 1] = std::stoi(number_copy.substr(0, number_copy.length() - max_power * (size - 1)));
    }
}

BigInt::BigInt(int32_t number) 
{
    *this = BigInt(std::to_string(number));
}

BigInt::BigInt(const BigInt& another_BigInt)
{
    size = another_BigInt.size;
    data = new int32_t[size];
    sign = another_BigInt.sign;
    for (size_t i = 0; i < size; i++)
        data[i] = another_BigInt.data[i];
}

BigInt::BigInt(BigInt&& another_BigInt) 
{
    size = another_BigInt.size;
    data = another_BigInt.data;
    sign = another_BigInt.sign;
    another_BigInt.data = nullptr;
    another_BigInt.size = 0;
    another_BigInt.sign = 1;
}

BigInt::~BigInt() 
{
    if (data != nullptr)
        delete[] data;
}

BigInt& BigInt::operator=(const BigInt& another_BigInt)
{
    int32_t* tmp;
    size = another_BigInt.size;
    sign = another_BigInt.sign;
    tmp = new int32_t[size];
    delete[] data;
    data = tmp;
    for (size_t i = 0; i < size; i++)
        data[i] = another_BigInt.data[i];
    return *this;
}

BigInt& BigInt::operator=(BigInt&& another_BigInt)
{
    delete[] data;
    size = another_BigInt.size;
    sign = another_BigInt.sign;
    data = another_BigInt.data;
    another_BigInt.data = nullptr;
    another_BigInt.size = 0;
    another_BigInt.sign = 1;
    return *this;
}

BigInt BigInt::operator+(const BigInt& another_BigInt) const
{
    if (sign != another_BigInt.sign)
    {
        if (sign == 1)
        {
            return *this - (-another_BigInt);
        }
        else
        {
            return another_BigInt - (-*this);
        }
    }

    BigInt res(std::max(size, another_BigInt.size) + 1);
    res.sign = sign;
    int32_t overload;
    for (size_t i = 0; i < res.size - 1; i++)
    {
        if ((i < size) && (i < another_BigInt.size))
        {
            res.data[i] = (data[i] + another_BigInt.data[i] + overload) % base;
            overload = (data[i] + another_BigInt.data[i] + overload) / base;
        }
        else
        {
            if (i < size)
            {
                res.data[i] = (data[i] + overload) % base;
                overload = (data[i] + overload) / base;
            }
            if (i < another_BigInt.size)
            {
                res.data[i] = (another_BigInt.data[i] + overload) % base;
                overload = (another_BigInt.data[i] + overload) / base;
            }
        }
    }
    if (overload > 0)
    {
        res.data[res.size - 1] = overload;
    }
    else
    {
        res.size--;
    }
    return res;
}

BigInt BigInt::operator+(int32_t number) const 
{
    return *this + BigInt(number);
}

BigInt BigInt::operator-(const BigInt& another_BigInt) const
{
    if (another_BigInt.sign == 0)
    {
        return *this + (-another_BigInt);
    }
    else
    {
        if (sign == 0)
        {
            return -(-*this + another_BigInt);
        }
        if (another_BigInt > *this)
        {
            return -(another_BigInt - *this);
        }
        BigInt res(size);
        int32_t borrowing = 0;
        for (size_t i = 0; i < size; i++)
        {
            if (i < another_BigInt.size)
            {
                if (data[i] >= another_BigInt.data[i] + borrowing)
                {
                    res.data[i] = data[i] - another_BigInt.data[i] - borrowing;
                    borrowing = 0;
                }
                else
                {
                    res.data[i] = base + data[i] - another_BigInt.data[i] - borrowing;
                    borrowing = 1;
                }
            }
            else
            {
                if (data[i] >= borrowing)
                {
                    res.data[i] = data[i] - borrowing;
                    borrowing = 0;
                }
                else
                {
                    res.data[i] = base + data[i] - borrowing;
                    borrowing = 1;
                }
            }
        }
        int32_t zero_parts = 0;
        for (size_t i = res.size - 1; i > 0; i--)
        {
            if (res.data[i] < 1)
            {
                zero_parts++;
            }
            else
            {
                break;
            }
        }
        res.size -= zero_parts;
        if ((res.size == 1) && (res.data[0] == 0))
        {
            res.sign = 1;
        }
        return res;
    }
}

BigInt BigInt::operator-(int32_t number) const 
{
    return *this - BigInt(number);
}

BigInt BigInt::operator-() const 
{
    BigInt tmp = *this;
    if ((data[0] > 0) || (size > 1))
        if (tmp.sign == 1)
        {
            tmp.sign = 0;
        }
        else
        {
            tmp.sign = 1;
        }
    return tmp;
}

BigInt BigInt::operator*(const BigInt& another_BigInt) const
{
    BigInt res(size + another_BigInt.size);
    res.sign = sign * another_BigInt.sign;
    for (size_t i = 0; i < res.size; i++)
    {
        res.data[i] = 0;
    }
    int32_t overload;
    for (size_t i = 0; i < another_BigInt.size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            int32_t tmp = res.data[i + j] + data[j] * another_BigInt.data[i] + overload;
            res.data[i + j] = tmp % base;
            overload = tmp / base;
        }
        if (overload > 0)
        {
            int32_t tmp = res.data[i + size] + overload;
            res.data[i + size] = tmp % base;
            overload = tmp / base;
        }
    }
    uint32_t zero_parts = 0;
    for (size_t i = res.size - 1; i > 0; i--)
        {
            if (res.data[i] == 0)
            {
                zero_parts++;
            }
            else
            {
                break;
            }
        }
    res.size -= zero_parts;
    if ((res.size == 1) && (res.data[0] == 0))
        {
            res.sign = 1;
        }
    return res;
}

BigInt BigInt::operator*(int32_t number) const 
{
    return *this * BigInt(number);
}

bool BigInt::operator==(const BigInt& another_BigInt) const
{
    if ((sign == another_BigInt.sign) && (size == another_BigInt.size))
    {
        for (size_t i = 0; i < size; i++)
        {
            if (data[i] != another_BigInt.data[i])
                return false;
        }
        return true;
    }
    return false;
}

bool BigInt::operator!=(const BigInt& another_BigInt) const
{
    return !(*this == another_BigInt);
}

bool BigInt::operator>(const BigInt& another_BigInt) const
{
    if (*this == another_BigInt)
        return false;
    if (sign > another_BigInt.sign)
        return true;
    if (another_BigInt.sign > sign)
        return false;
    if (sign > 0)
    {
        if (size > another_BigInt.size)
            return true;
        if (another_BigInt.size > size)
            return false;
    }
    if (sign == 0)
    {
        if (size > another_BigInt.size)
            return false;
        if (another_BigInt.size > size)
            return true;
    }
    if (sign == 0) 
    {
        for (size_t i = size; i > 0; i--)
            if (data[i - 1] != another_BigInt.data[i - 1])
                return data[i - 1] < another_BigInt.data[i - 1];
    }
    else
    {
        for (size_t i = size; i > 0; i--)
            if (data[i - 1] != another_BigInt.data[i - 1])
                return data[i - 1] > another_BigInt.data[i - 1];
    }
    return false;
}

bool BigInt::operator>=(const BigInt& another_BigInt) const 
{
    return (*this == another_BigInt) || (*this > another_BigInt);
}

bool BigInt::operator<(const BigInt& another_BigInt) const 
{
    return !(*this >= another_BigInt);
}

bool BigInt::operator<=(const BigInt& another_BigInt) const 
{
    return !(*this > another_BigInt);
}

std::ostream& operator<<(std::ostream& out, const BigInt& number) 
{
    if (number.size == 0)
        out << 0;
    else {
        if (number.sign == 0)
            out << '-';
        out << number.data[number.size - 1];
        for (size_t i = number.size - 1; i > 0; i--) {
            std::string tmp = std::to_string(number.data[i - 1]);
            if (tmp.length() < number.max_power)
                for (size_t j = tmp.length(); j < number.max_power; j++)
                    out << 0;
            out << tmp;
        }
    }
    return out;
}