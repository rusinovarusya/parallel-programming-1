#include "Matrix.h"

Matrix createZeroMatrix(size_t rows, size_t columns) {
	Matrix matrix;
	matrix.rowsCount = rows;
	matrix.columnsCount = columns;
	matrix.matrix = new int*[matrix.rowsCount];
	for (size_t i = 0; i < matrix.rowsCount; ++i) {
		matrix.matrix[i] = new int[matrix.columnsCount];
		for (size_t j = 0; j < matrix.columnsCount; ++j) {
			matrix.matrix[i][j] = 0;
		}
	}
	return matrix;
}

Matrix createRandomMatrix(size_t rows, size_t columns) {
	Matrix matrix;
	matrix.rowsCount = rows;
	matrix.columnsCount = columns;

	matrix.matrix = new int*[matrix.rowsCount];
	for (size_t i = 0; i < matrix.rowsCount; ++i) {
		matrix.matrix[i] = new int[matrix.columnsCount];
		for (size_t j = 0; j < matrix.columnsCount; ++j) {
			matrix.matrix[i][j] = rand();
		}
	}
	return matrix;
}
void printMatrix(Matrix matrix) {
	std::cout << "\n";
	for (size_t i = 0; i < matrix.rowsCount; ++i) {
		for (size_t j = 0; j < matrix.columnsCount; ++j) {
			std::cout << matrix.matrix[i][j] << '\t';
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
