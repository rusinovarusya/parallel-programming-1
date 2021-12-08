#include <iostream>
#include <vector>

using namespace std; 

int getFirstDigit(int number) {
	int divider = 1;
	while (number  >= divider * 10) {
		divider *= 10;
	}
	return number / divider;
}

int** createMatrix(int rows, int columns) {
	int** matrix = new int*[rows];
	for (int i = 0; i < rows; ++i) {
		matrix[i] = new int[columns];
		for (int j = 0; j < columns; ++j) {
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

int** createRandomMatrix(int rows, int columns) {
	int** matrix = new int*[rows];
	for (int i = 0; i < rows; ++i) {
		matrix[i] = new int[columns];
		for (int j = 0; j < columns; ++j) {
			matrix[i][j] = rand();
		}
	}
	return matrix;
}

void printMatrix(int** matrix, int rows, int columns) {
	cout << "\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			cout << matrix[i][j] << '\t';
		}
		cout << "\n";
	}
	cout << "\n";
}

int findFirstNumber_nonparallel(int** matrix, int rows, int columns, int digit) {
	int result;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (getFirstDigit(matrix[i][j]) == digit) {
				result = matrix[i][j];
			}
		}
	}
	return result;
}

int min_nonparallel(int** matrix, int rows, int columns, int digit) {
	int min = findFirstNumber_nonparallel(matrix, rows, columns, digit);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			int firstDigit = getFirstDigit(matrix[i][j]);
			if (firstDigit == digit) {
				if (matrix[i][j] < min) {
					min = matrix[i][j];
				}
			}
		}
	}
	return min;
}

int main() {
	const int rowsCount = 4;
	const int columnsCount = 5;

	int** matrix = createRandomMatrix(rowsCount, columnsCount);
	printMatrix(matrix, rowsCount, columnsCount);

	cout << min_nonparallel(matrix, rowsCount, columnsCount, 1) << '\n';
	
	system("pause");
	return 0;
}
