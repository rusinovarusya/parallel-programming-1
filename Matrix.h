#pragma once
#include <iostream>

using namespace std;

struct Matrix {
	int rowsCount;
	int columnsCount;
	int** matrix;
};

Matrix createZeroMatrix(int rows, int columns);
Matrix createRandomMatrix(int rows, int columns);
void printMatrix(Matrix matrix);