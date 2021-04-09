#include <iostream>

#include "matrix.hpp"

Matrix::ProxyRow::ProxyRow (size_t cols_)
{
    cols = cols_;
    row = new int32_t[cols];
    for (size_t i=0; i<cols; i++)
    {
        row[i] = 0;
    }
}

int& Matrix::ProxyRow::operator[](size_t i)
{
    if (i >= cols)
    {
            throw std::out_of_range("column index out of range");
    }
    return row[i];
}

const int& Matrix::ProxyRow::operator[](size_t i) const
{
    if (i >= cols)
    {
            throw std::out_of_range("column index out of range");
    }
    return row[i];
}

size_t Matrix::ProxyRow::getColumns() const
{
    return cols;
}

Matrix::ProxyRow& Matrix::ProxyRow::operator=(const Matrix::ProxyRow& rsh)
{
    if (row != rsh.row)
    {
        if (row != nullptr)
        {
            delete[] row;
        }
        cols = rsh.cols;
        row = new int32_t[cols];
        for (size_t i=0; i<cols; i++)
        {
            row[i] = rsh.row[i];
        }
    }
    return *this;
}

bool Matrix::ProxyRow::operator==(const Matrix::ProxyRow& rsh)
{
    if ((cols != rsh.cols))
    {
        return false;
    }
    for (size_t i=0; i<cols; i++)
    {
        if (row[i]!=rsh.row[i])
        {
            return false;
        }
    }
    return true;
}

bool Matrix::ProxyRow::operator!=(const Matrix::ProxyRow& rsh)
{
    return !(*this == rsh);
}

Matrix::ProxyRow Matrix::ProxyRow::operator*=(int32_t num)
{
    for (size_t i=0; i<cols; i++)
    {
        row[i]*=num;
    }
    return *this;
}

Matrix::ProxyRow Matrix::ProxyRow::operator+(const Matrix::ProxyRow& rsh)
{
    if ((cols != rsh.cols))
    {
        throw std::out_of_range("rows have different dimensions");
    }
    Matrix::ProxyRow res(cols);
    for (size_t i=0; i<cols; i++)
    {
        res[i]=row[i] + rsh.row[i];
    }
    return res;
}

Matrix::ProxyRow::~ProxyRow()
{
    delete[] row;
}

Matrix::Matrix(size_t cols_, size_t rows_)
{
    cols = cols_;
    rows = rows_;
    matrix = new Matrix::ProxyRow[rows];
    for (size_t i=0; i<rows; i++)
    {
        matrix[i] = Matrix::ProxyRow(cols);
    }
}

Matrix::ProxyRow& Matrix::operator[](size_t i)
{
    if (i >= rows)
    {
            throw std::out_of_range("row index out of range");
    }
    return matrix[i];
}

const Matrix::ProxyRow& Matrix::operator[](size_t i) const
{
    if (i >= rows)
    {
            throw std::out_of_range("row index out of range");
    }
    return matrix[i];
}

size_t Matrix::getColumns() const
{
    return cols;
}

size_t Matrix::getRows() const
{
    return rows;
}

bool Matrix::operator==(const Matrix& rsh)
{
    if ((cols != rsh.cols) || (rows != rsh.rows))
    {
        return false;
    }
    for (size_t i=0; i<rows; i++)
    {
        if (matrix[i]!=rsh[i])
        {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& rsh)
{
    return !(*this == rsh);
}

Matrix& Matrix::operator=(const Matrix& rsh)
{
    if (matrix != rsh.matrix)
    {
        if (matrix != nullptr)
        {
            delete[] matrix;
        }
    cols = rsh.cols;
    rows = rsh.rows;
    matrix = new Matrix::ProxyRow[rows];
    for (size_t i=0; i<rows; i++)
        {
            matrix[i] = rsh.matrix[i];
        }
    }
    return *this;
}

Matrix Matrix::operator*=(int32_t num)
{
    for (size_t i=0; i<rows; i++)
    {
        matrix[i]*=num;
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& rsh)
{
    if ((cols != rsh.cols) || (rows != rsh.rows))
    {
        throw std::out_of_range("matrices have different dimensions");
    }
    Matrix res(cols, rows);
    for (size_t i=0; i<rows; i++)
    {
        res[i]=matrix[i] + rsh[i];
    }
    return res;
}

Matrix::~Matrix()
{
    delete[] matrix;
}

std::ostream& operator<<(std::ostream& out, const Matrix::ProxyRow& row)
{
    auto cols = row.getColumns(); 
    for (size_t i=0; i<cols; i++)
    {
        out << row.row[i] << ' ';
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
{
    auto rows = matrix.getRows();
    for (size_t i=0; i<rows; i++)
    {
        out << matrix.matrix[i] << std::endl;
    }
    return out;
}
