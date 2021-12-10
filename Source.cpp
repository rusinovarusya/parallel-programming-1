#include <iostream>
#include "Matrix.h"

#include <thread>
#include <mutex>
#include <Windows.h>
#include <vector>

std::mutex m;

const size_t COUNT = 110;
const size_t MAX_THREAD = 4;

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


void minNumber(Matrix matrix, size_t start, size_t end, int digit, int& global_min) {
	int local_min;
	if (isNumberStartingWithGivenDigit(matrix, start, end, digit)) {
		local_min = getFirstNumberStartingWithGivenDigit(matrix, start, end, digit);
	}

	for (size_t j = start % matrix.columnsCount; j < matrix.columnsCount; ++j) {

		if (getFirstDigit(matrix.matrix[start / matrix.columnsCount][j]) == digit) {
			if (matrix.matrix[start / matrix.columnsCount][j] < local_min) {
				local_min = matrix.matrix[start / matrix.columnsCount][j];
			}
		}
	}

	for (size_t i = start / matrix.columnsCount + 1; i < end / matrix.columnsCount; ++i) {
		for (size_t j = 0; j < matrix.columnsCount; ++j) {

			if (getFirstDigit(matrix.matrix[i][j]) == digit) {
				if (matrix.matrix[i][j] < local_min) {
					local_min = matrix.matrix[i][j];
				}
			}
		}
	}

	for (size_t j = 0; j < end % matrix.columnsCount + 1; ++j) {

		if (getFirstDigit(matrix.matrix[end / matrix.columnsCount][j]) == digit) {
			if (matrix.matrix[end / matrix.columnsCount][j] < local_min) {
				local_min = matrix.matrix[end / matrix.columnsCount][j];
			}
		}
	}

	std::lock_guard<std::mutex> lock(m);
	if (global_min > local_min) {
		global_min = local_min;
	}
}

int min_parallel(Matrix matrix, int digit) {
	const size_t min_block = 25;
	const size_t max_threads = (COUNT + min_block - 1) / min_block;
	const size_t hardware_threads = std::thread::hardware_concurrency();
	const size_t count_threads = min(hardware_threads != 0 ? hardware_threads : MAX_THREAD, max_threads) - 1;
	const size_t block_size = COUNT / (count_threads + 1);


	
	int global_min = getFirstNumberStartingWithGivenDigit(matrix, 0, matrix.rowsCount*matrix.columnsCount - 1, digit);
	std::vector<std::thread> threads(count_threads);
	for (size_t i = 0; i < count_threads; i++) {
		threads[i] = std::thread(minNumber, matrix, block_size*i, block_size*(i + 1), std::ref(global_min));
	}
	minNumber(matrix, block_size*count_threads, COUNT, digit, global_min);

	for (auto &i : threads) {
		i.join();
	}

	return global_min;
}


int main() {
	const size_t rowsCount = 10;
	const size_t columnsCount = 10;
	const int firstDigit = 1;

	Matrix matrix = createRandomMatrix(rowsCount, columnsCount);
	printMatrix(matrix);
	std::cout << "1. min number starting with " << firstDigit << " is:\n";
	std::cout << "nonparallel " << min_nonparallel(matrix, firstDigit) << '\n';
	std::cout << "parallel " << min_parallel(matrix, firstDigit) << '\n';


	Matrix matrix2 = createZeroMatrix(rowsCount, columnsCount);
	printMatrix(matrix2);
	try {
		std::cout << min_nonparallel(matrix2, firstDigit) << '\n';
	}
	catch (std::logic_error& e) {
		std::cout << e.what() << '\n';
	}

	int minValue = getFirstNumberStartingWithGivenDigit(matrix, 0, matrix.rowsCount * matrix.columnsCount - 1, firstDigit); // remove
	minNumber(matrix, 0, matrix.rowsCount * matrix.columnsCount - 1, firstDigit, minValue);
	std::cout << "with function minNumber " << minValue << '\n';

	system("pause");
	return 0;
}
