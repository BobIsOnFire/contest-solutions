#include <iostream>
using namespace std;

int swap(double *a, double *b) {
	double t = *a;
	*a = *b;
	*b = t;
}

void quick_sort(double arr[], int low, int high) {
	if (low <  high) {
		double pivot = arr[high];
		int k = (low - 1);

		for (int i = low; i < high; i++) {
			if (arr[i] < pivot) {
				k++;
				swap(&arr[i], &arr[k]);
			}
		}
		k++;
		swap(&arr[k], &arr[high]);

		quick_sort(arr, low, k - 1);
		quick_sort(arr, k + 1, high);
	}
}

int main() {
	int N;
	cin >> N;
	int min_i = 0;
	int x[N], y[N];

	for (int i = 0; i < N; i++) {
		cin >> x[i] >> y[i];
		if (x[i] < x[min_i]) min_i = i;
	}

	double tan[N];
	tan[min_i] = - (2E6 + 2);
	for (int i = 0; i < N; i++) {
		if (i == min_i) continue;
		if (x[i] == x[min_i]) {
			tan[i] = (2E6 + 1) * ((y[i] - y[min_i]) > 0 ? 1 : -1);
			continue;
		}

		tan[i] = (y[i] - y[min_i]) * 1.0 / (x[i] - x[min_i]);
	}

	double tan_sort[N];
	for (int i = 0; i < N; i++) tan_sort[i] = tan[i];
	quick_sort(tan_sort, 0, N - 1);

	double median = tan_sort[N / 2];
	for (int i = 0; i < N; i++) {
		if (tan[i] == median) {
			cout << (min_i + 1) << ' ' << (i + 1) << endl;
			return 0;
		}
	}

}
