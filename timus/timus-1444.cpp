#include <iostream>
#include <math.h>
using namespace std;

bool cmp(double a[], double b[]) {
	if (a[1] != b[1]) return a[1] < b[1];
	return a[2] < b[2];
}

void swap(double a[], double b[], int size) {
	double t;
        for (int i = 0; i < size; i++) {
	        t = a[i];
                a[i] = b[i];
                b[i] = t;
        }
}

int quick_sort(double arr[][3], int low, int high) {
        if (low < high) {
                int k = low - 1;
                double* pivot = arr[high];
                for (int i = low; i < high; i++) {
	                double* current = arr[i];
                        if (cmp(current, pivot)) {
                                k++;
                                swap(current, arr[k], 3);
                        }
                }

		k++;
                swap(arr[k], arr[high], 3);

                quick_sort(arr, low, k - 1);
                quick_sort(arr, k + 1, high);
	}
}

int main() {
	int N;
	cin >> N;

	int x0, y0, x, y;
	cin >> x0 >> y0;
	double data[N - 1][3];

	for (int i = 0; i < N - 1; i++) {
		cin >> x >> y;
		data[i][0] = i + 2;
		data[i][1] = atan2(y - y0, x - x0);
		data[i][2] = (x - x0) * cos(data[i][1]);
		if (data[i][2] == 0) data[i][2] = abs(y - y0);
	}

	quick_sort(data, 0, N - 2);

	double PI = acos(-1);
	int start = 0;
	for (int i = 1; i < N - 1; i++) {
		if (data[i][1] - data[i - 1][1] >= PI) {
			start = i;
			break;
		}
	}

	cout << N << endl;
	cout << 1 << endl;
	cout << data[start][0] << endl;

	int k = (start + 1) % (N - 1);
	while (k != start) {
		cout << data[k][0] << endl;
		k = (k + 1) % (N - 1);
	}
}
