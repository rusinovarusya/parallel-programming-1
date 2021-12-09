#include <iostream>
#include <vector>
#include "Matrix.h"

using namespace std; 

int getFirstDigit(int number) {
	int divider = 1;
	while (number  >= divider * 10) {
		divider *= 10;
	}
	return number / divider;
}

bool isNumberStartingWithGivenDigit_nonparallel(Matrix matrix, int digit) {
	for (int i = 0; i < matrix.rowsCount; ++i) {
		for (int j = 0; j < matrix.columnsCount; ++j) {
			if (getFirstDigit(matrix.matrix[i][j]) == digit) {
				return true;
			}
		}
	}
	return false;
}

int getFirstNumberStartingWithGivenDigit_nonparallel(Matrix matrix, int digit) {
	for (int i = 0; i < matrix.rowsCount; ++i) {
		for (int j = 0; j < matrix.columnsCount; ++j) {
			if (getFirstDigit(matrix.matrix[i][j]) == digit) {
				return matrix.matrix[i][j];
			}
		}
	}
	return matrix.matrix[0][0];
}

int min_nonparallel(Matrix matrix, int digit) {
	int min;
	if (isNumberStartingWithGivenDigit_nonparallel(matrix, digit)) {
		min = getFirstNumberStartingWithGivenDigit_nonparallel(matrix, digit);
	}
	for (int i = 0; i < matrix.rowsCount; ++i) {
		for (int j = 0; j < matrix.columnsCount; ++j) {
			int firstDigit = getFirstDigit(matrix.matrix[i][j]);
			if (firstDigit == digit) {
				if (matrix.matrix[i][j] < min) {
					min = matrix.matrix[i][j];
				}
			}
		}
	}
	return min;
}

int main() {
	const int rowsCount = 4;
	const int columnsCount = 5;

	Matrix matrix = createRandomMatrix(rowsCount, columnsCount);
	printMatrix(matrix);
	cout << min_nonparallel(matrix, 2) << '\n';

	system("pause");
	return 0;
}
