#include <cassert>
#include <iostream>
#include <sstream>

#include "matrix.hpp"


void get_operator_test()
{
    size_t rows = 10;
    size_t cols = 5;
    Matrix matrix(cols, rows);
    assert(matrix.getRows() == rows);
    assert(matrix.getColumns() == cols);
    std::cout << "get operator test : Done" << std::endl;
}

void brackets_operator_test()
{
    size_t rows = 10;
    size_t cols = 5;
    Matrix matrix(cols, rows);
    for (size_t i=0; i<rows; i++)
        for (size_t j=0; j<cols; j++)
        {
            matrix[i][j] = int(i*cols + j + 1);
            assert(matrix[i][j] == int(i*cols + j + 1));
        }
    std::cout << "[] operator test : Done" << std::endl;
}

void equal_operator_test()
{
    size_t rows = 10;
    size_t cols = 5;
    Matrix matrix(cols, rows);
    Matrix matrix2(cols, rows);
    Matrix matrix3(cols, rows);
    for (size_t i=0; i<rows; i++)
        for (size_t j=0; j<cols; j++)
        {
            matrix[i][j] = int(i*cols + j + 1);
            matrix2[i][j] = int(i*cols + j + 1);
        }
    assert((matrix == matrix2)&&(matrix != matrix3) == true);
    std::cout << "equal and unequal operator test : Done" << std::endl;
}

void matrix_summator_test()
{
    size_t rows = 10;
    size_t cols = 5;
    Matrix matrix(cols, rows);
    Matrix matrix2(cols, rows);
    Matrix matrix3(cols, rows);
    for (size_t i=0; i<rows; i++)
        for (size_t j=0; j<cols; j++)
        {
            matrix[i][j] = 1;
            matrix2[i][j] = 2;
            matrix3[i][j] = 3;
        }
    assert(matrix + matrix2 == matrix3);
    std::cout << "+ operator test : Done" << std::endl;
}

void matrix_multiply_test()
{
    size_t rows = 10;
    size_t cols = 5;
    Matrix matrix(cols, rows);
    Matrix matrix2(cols, rows);
    for (size_t i=0; i<rows; i++)
        for (size_t j=0; j<cols; j++)
        {
            matrix[i][j] = 1;
            matrix2[i][j] = 5;
        }
    assert((matrix *= 5) == matrix2);
    std::cout << "=* operator test : Done" << std::endl;
}

void assignment_test()
{
    size_t rows = 10;
    size_t cols = 5;
    Matrix matrix(cols, rows);
    Matrix matrix2(cols, rows);
    Matrix matrix3(cols, rows);
    for (size_t i=0; i<rows; i++)
        for (size_t j=0; j<cols; j++)
        {
            matrix[i][j] = 1;
            matrix2[i][j] = 1;
        }
    matrix3 = matrix;
    assert(matrix3 == matrix2);
    std::cout << "assignment operator test : Done" << std::endl;
}

void output_test()
{
    std::stringstream output;
    size_t rows = 3;
    size_t cols = 3;
    Matrix matrix(cols, rows);
    output << matrix;
    assert(output.str() == "0 0 0 \n0 0 0 \n0 0 0 \n");
    std::cout << "output test : Done" << std::endl;
}

int main()
{
    get_operator_test();
    brackets_operator_test();
    equal_operator_test();
    matrix_summator_test();
    matrix_multiply_test();
    assignment_test();
    output_test();
}