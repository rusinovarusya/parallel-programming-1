#pragma once
#include <iostream>

struct Matrix {
	size_t rowsCount;
	size_t columnsCount;
	int** matrix;
};

Matrix createZeroMatrix(size_t rows, size_t columns);
Matrix createRandomMatrix(size_t rows, size_t columns);
void printMatrix(Matrix matrix);
