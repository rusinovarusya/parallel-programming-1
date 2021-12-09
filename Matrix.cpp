#include "Matrix.h"

Matrix createZeroMatrix(int rows, int columns) {
	Matrix matrix;
	matrix.rowsCount = rows;
	matrix.columnsCount = columns;
	matrix.matrix = new int*[matrix.rowsCount];
	for (int i = 0; i < matrix.rowsCount; ++i) {
		matrix.matrix[i] = new int[matrix.columnsCount];
		for (int j = 0; j < matrix.columnsCount; ++j) {
			matrix.matrix[i][j] = 0;
		}
	}
	return matrix;
}

Matrix createRandomMatrix(int rows, int columns) {
	Matrix matrix;
	matrix.rowsCount = rows;
	matrix.columnsCount = columns;

	matrix.matrix = new int*[matrix.rowsCount];
	for (int i = 0; i < matrix.rowsCount; ++i) {
		matrix.matrix[i] = new int[matrix.columnsCount];
		for (int j = 0; j < matrix.columnsCount; ++j) {
			matrix.matrix[i][j] = rand();
		}
	}
	return matrix;
}
void printMatrix(Matrix matrix) {
	cout << "\n";
	for (int i = 0; i < matrix.rowsCount; ++i) {
		for (int j = 0; j < matrix.columnsCount; ++j) {
			cout << matrix.matrix[i][j] << '\t';
		}
		cout << "\n";
	}
	cout << "\n";
}
