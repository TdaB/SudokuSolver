#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

#define N 9



void print_grid(int grid[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

bool in_row(int grid[N][N], int val, int row) {
	for (int i = 0; i < N; i++) {
		if (grid[row][i] == val) {
			return true;
		}
	}
	return false;
}

bool in_col(int grid[N][N], int val, int col) {
	for (int i = 0; i < N; i++) {
		if (grid[i][col] == val) {
			return true;
		}
	}
	return false;
}

bool in_3x3(int grid[N][N], int val, int row, int col) {
	int row_start, col_start;
	if (row >= 0 && row <= 2) {
		row_start = 0;
	}
	if (row >= 3 && row <= 5) {
		row_start = 3;
	}
	if (row >= 6 && row <= 8) {
		row_start = 6;
	}

	if (col >= 0 && col <= 2) {
		col_start = 0;
	}
	if (col >= 3 && col <= 5) {
		col_start = 3;
	}
	if (col >= 6 && col <= 8) {
		col_start = 6;
	}

	for (int r = row_start; r < row_start + 3; r++) {
		for (int c = col_start; c < col_start + 3; c++) {
			if (val == grid[r][c]) {
				return true;
			}
		}
	}
	return false;
}

bool is_valid_move(int grid[N][N], int val, int row, int col) {
	return !in_row(grid, val, row) && !in_col(grid, val, col) && !in_3x3(grid, val, row, col);
}

//bool check_9-OLD(vector<int> v) {
//	vector<int> nums;
//	for (int n = 1; n <= N; n++) {
//		nums.push_back(n);
//	}
//	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
//		cout << *it;
//		for (vector<int>::iterator it_nums = nums.begin(); it_nums != nums.end(); ++it_nums) {
//			cout << *it_nums;
//			if (*it_nums == *it) {
//				// Erase from nums
//				nums.erase(remove(nums.begin(), nums.end(), *it), nums.end());
//			}
//		}
//	}
//	return nums.size() == 0;
//}

//int * get_col(int grid[N][N], int col) {
//	int c[9];
//	for (int i = 0; i < N; i++) {
//		c[i] = grid[i][col];
//	}
//	return c;
//}

//int * get_3x3(int grid[N][N], int row, int col) {
//	int row_start, col_start;
//	int vals[N];
//	int index = 0;
//
//	if (row >= 0 && row <= 2) {
//		row_start = 0;
//	}
//	if (row >= 3 && row <= 5) {
//		row_start = 3;
//	}
//	if (row >= 6 && row <= 8) {
//		row_start = 6;
//	}
//
//	if (col >= 0 && col <= 2) {
//		col_start = 0;
//	}
//	if (col >= 3 && col <= 5) {
//		col_start = 3;
//	}
//	if (col >= 6 && col <= 8) {
//		col_start = 6;
//	}
//
//	for (int r = row_start; r < row_start + 3; r++) {
//		for (int c = col_start; c < col_start + 3; c++) {
//			vals[index] = grid[r][c];
//			index++;
//		}
//	}
//	return vals;
//}

//int * get_3x3(int grid[N][N], int row, int col) {
//	int vals[N];
//	int index = 0;
//
//	for (int r = row; r < row + 3; r++) {
//		for (int c = col; c < col + 3; c++) {
//			vals[index] = grid[r][c];
//			index++;
//		}
//	}
//	return vals;
//}

// Check to see if we have numbers 1 - 9
// in a row, col, or 3x3 slice
bool check_9(int slice[9]) {
	int nums[9];
	for (int i = 0; i < 9; i++) {
		nums[i] = i + 1;
	}

	for (int i = 0; i < 9; i++) {
		for (int n = 0; n < 9; n++) {
			if (slice[i] == 0) {
				return false;
			}
			if (slice[i] == nums[n]) {
				nums[n] = 0;
			}
		}
	}

	for (int n = 0; n < 9; n++) {
		if (nums[n] != 0) {
			return false;
		}
	}
	return true;
}


bool is_solved(int grid[N][N]) {
	// Check rows
	for (int r = 0; r < N; r++) {
		if (!check_9(grid[r])) {
			return false;
		}
	}

	// Check cols
	for (int c = 0; c < N; c++) {
		//int * col = get_col(grid, c);
		int col[9];
		for (int i = 0; i < N; i++) {
			col[i] = grid[i][c];
		}
		if (!check_9(col)) {
			return false;
		}
	}
	
	// Check 3x3s
	for (int r = 0; r < N; r = r + 3) {
		for (int c = 0; c < N; c = c + 3) {
			//int * my_3x3 = get_3x3(grid, r, c);

			int vals[N];
			int index = 0;

			for (int rr = r; rr < r + 3; rr++) {
				for (int cc = c; cc < c + 3; cc++) {
					vals[index] = grid[rr][cc];
					index++;
				}
			}

			if (!check_9(vals)) {
				return false;
			}
		}
	}

	return true;
}

bool solve(int grid[N][N]) {
//this_thread::sleep_for(chrono::milliseconds(500));
//print_grid(grid);
//cout << endl;

	if (is_solved(grid)) {
		cout << "SOLVED!" << endl;
		print_grid(grid);
		return true;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int val = grid[i][j];
			if (val == 0) {
				for (int next_try = 1; next_try <= N; next_try++) {
					if (is_valid_move(grid, next_try, i, j)) {
						grid[i][j] = next_try;
						if (solve(grid)) {
							return true;
						}
					}
				}
				grid[i][j] = 0;
				return false;
			}	
		}
	}
	return false;
}

int main() {
	int grid[N][N] = {
		{ 3, 0, 6, 5, 0, 8, 4, 0, 0 },
		{ 5, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 8, 7, 0, 0, 0, 0, 3, 1 },
		{ 0, 0, 3, 0, 1, 0, 0, 8, 0 },
		{ 9, 0, 0, 8, 6, 3, 0, 0, 5 },
		{ 0, 5, 0, 0, 9, 0, 6, 0, 0 },
		{ 1, 3, 0, 0, 0, 0, 2, 5, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 7, 4 },
		{ 0, 0, 5, 2, 0, 6, 3, 0, 0 }
	};

	int solved[N][N] = {
		{ 4, 3, 5, 2, 6, 9, 7, 8, 1 },
		{ 6, 8, 2, 5, 7, 1, 4, 9, 3 },
		{ 1, 9, 7, 8, 3, 4, 5, 6, 2 },
		{ 8, 2, 6, 1, 9, 5, 3, 4, 7 },
		{ 3, 7, 4, 6, 8, 2, 9, 1, 5 },
		{ 9, 5, 1, 7, 4, 3, 6, 2, 8 },
		{ 5, 1, 9, 3, 2, 6, 8, 7, 4 },
		{ 2, 4, 8, 9, 5, 7, 1, 3, 6 },
		{ 7, 6, 3, 4, 1, 8, 2, 5, 9 }
	};

	int unsolvable[N][N] = {
		{ 1, 2, 3, 4, 5, 6, 7, 8, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 5 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 6 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 7 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 8 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 9 },
	};

	cout << solve(grid);
	
	return 0;
}