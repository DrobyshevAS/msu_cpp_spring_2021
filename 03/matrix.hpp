#pragma once
#include <iostream>

class Matrix
{
    public:
        class ProxyRow
        {
            private:
                size_t cols;
                int32_t* row;

            public:
                ProxyRow() = default;
                ProxyRow(size_t cols_);
                int& operator[](size_t i);
                const int& operator[](size_t i) const;
                size_t getColumns() const;
                bool operator==(const ProxyRow& rsh);
                bool operator!=(const ProxyRow& rsh);
                ProxyRow operator*=(int32_t num);
                ProxyRow& operator=(const ProxyRow& rsh);
                ProxyRow operator+(const ProxyRow& rsh);
                ~ProxyRow();
                friend std::ostream& operator<<(std::ostream& out, const ProxyRow& row);
        };
        Matrix(size_t cols_, size_t rows);
        ProxyRow& operator[](size_t i);
        const ProxyRow& operator[](size_t i) const;
        size_t getColumns() const;
        size_t getRows() const;
        Matrix& operator=(const Matrix& rsh);
        Matrix operator*=(int32_t num);
        Matrix operator+(const Matrix& rsh);
        bool operator==(const Matrix& rsh);
        bool operator!=(const Matrix& rsh);
        ~Matrix();
        friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

    private:
        size_t rows;
        size_t cols;
        ProxyRow* matrix;

};
