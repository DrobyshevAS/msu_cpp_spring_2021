#pragma once
#include <iostream>

class Matrix
{
    public:
        class ProxyRow
        {
            private:
                size_t cols = 0;
                int32_t* row = nullptr;

            public:
                ProxyRow() = default;
                ProxyRow(size_t cols_);
                int32_t& operator[](size_t i);
                const int32_t& operator[](size_t i) const;
                size_t getColumns() const;
                bool operator==(const ProxyRow& rsh) const;
                bool operator!=(const ProxyRow& rsh) const;
                ProxyRow& operator*=(int num);
                ProxyRow& operator=(const ProxyRow& rsh);
                ProxyRow operator+(const ProxyRow& rsh) const;
                friend std::ostream& operator<<(std::ostream& out, const ProxyRow& row);
        };
        Matrix(size_t cols_, size_t rows);
        ProxyRow& operator[](size_t i);
        const ProxyRow& operator[](size_t i) const;
        size_t getColumns() const;
        size_t getRows() const;
        Matrix& operator=(const Matrix& rsh);
        Matrix& operator*=(int32_t num);
        Matrix operator+(const Matrix& rsh) const;
        bool operator==(const Matrix& rsh) const;
        bool operator!=(const Matrix& rsh) const;
        ~Matrix();
        friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

    private:
        size_t rows = 0;
        size_t cols = 0;
        ProxyRow* matrix = nullptr;

};