#include <bits/stdc++.h>
#include <math.h>
using namespace std;

int** field;
int counter = 1;

void fill(int size, int top, int left, int i, int j) {
	int mid_i = top + size / 2;
	int mid_j = left + size / 2;

	bool check_i = i >= mid_i;
	bool check_j = j >= mid_j;

	if (check_i || check_j) field[mid_i - 1][mid_j - 1] = counter;
	if (check_i || !check_j) field[mid_i - 1][mid_j] = counter;
	if (!check_i || check_j) field[mid_i][mid_j - 1] = counter;
	if (!check_i || !check_j) field[mid_i][mid_j] = counter;
	counter++;

	if (size == 2) return;

	if (check_i) {
		fill(size / 2, top, left, mid_i - 1, mid_j - 1);
		fill(size / 2, top, mid_j, mid_i - 1, mid_j);

		if (check_j) {
			fill(size / 2, mid_i, left, mid_i, mid_j - 1);
			fill(size / 2, mid_i, mid_j, i, j);
		}
		else {
			fill(size / 2, mid_i, left, i, j);
			fill(size / 2, mid_i, mid_j, mid_i, mid_j);
		}
	}
	else {
		fill(size / 2, mid_i, left, mid_i, mid_j - 1);
		fill(size / 2, mid_i, mid_j, mid_i, mid_j);

		if (check_j) {
			fill(size / 2, top, left, mid_i - 1, mid_j - 1);
			fill(size / 2, top, mid_j, i, j);
		}
		else {
			fill(size / 2, top, mid_j, mid_i - 1, mid_j);
			fill(size / 2, top, left, i, j);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	int i, j;
	cin >> i >> j;
	i--, j--;

	int size = pow(2, N);
	field = new int*[size];
	for (int k = 0; k < size; k++) {
		field[k] = new int[size];
	}

	field[i][j] = 0;
	fill(size, 0, 0, i, j);
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			cout << field[i][j] << ' ';
		}
		cout << endl;
	}

	return 0;
}
