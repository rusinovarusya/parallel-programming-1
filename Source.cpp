#include <iostream>
#include "Matrix.h"

int getFirstDigit(int number) {
	int divider = 1;
	while (number  >= divider * 10) {
		divider *= 10;
	}
	return number / divider;
}

bool isNumberStartingWithGivenDigit(Matrix matrix, size_t start, size_t end, int digit) {
	for (size_t i = start / matrix.columnsCount; i < end / matrix.columnsCount + 1; ++i) {
		for (size_t j = start % matrix.columnsCount; j < end % matrix.columnsCount + 1; ++j) {
			if (getFirstDigit(matrix.matrix[i][j]) == digit) {
				return true;
			}
		}
	}
	return false;
}

int getFirstNumberStartingWithGivenDigit(Matrix matrix, size_t start, size_t end, int digit) {
	for (size_t i = start / matrix.columnsCount; i < end / matrix.columnsCount + 1; ++i) {
		for (size_t j = start % matrix.columnsCount; j < end % matrix.columnsCount + 1; ++j) {
			if (getFirstDigit(matrix.matrix[i][j]) == digit) {
				return matrix.matrix[i][j];
			}
		}
	}
	return matrix.matrix[0][0];
}

int min_nonparallel(Matrix matrix, int digit) {
	int min;
	if (isNumberStartingWithGivenDigit(matrix, 0, matrix.rowsCount * matrix.columnsCount - 1, digit)) {
		min = getFirstNumberStartingWithGivenDigit(matrix, 0, matrix.rowsCount * matrix.columnsCount - 1, digit);
	}
	else {
		throw std::logic_error("There are not numbers starting with a given digit");
	}

	for (size_t i = 0; i < matrix.rowsCount; ++i) {
		for (size_t j = 0; j < matrix.columnsCount; ++j) {
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
	const size_t rowsCount = 11;
	const size_t columnsCount = 10;
	const int firstDigit = 1;

	Matrix matrix = createRandomMatrix(rowsCount, columnsCount);
	printMatrix(matrix);
	std::cout << "1. min number starting with " << firstDigit << " is " << min_nonparallel(matrix, firstDigit) << '\n';
	

	Matrix matrix2 = createZeroMatrix(rowsCount, columnsCount);
	printMatrix(matrix2);
	try {
		std::cout << min_nonparallel(matrix2, firstDigit) << '\n';
	}
	catch (std::logic_error& e) {
		std::cout << e.what() << '\n';
	}

	system("pause");
	return 0;
}
