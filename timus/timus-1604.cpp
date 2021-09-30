#include <iostream>
using namespace std;

void swap_rows(int a[], int b[], int size) {
	int t;
	for (int i = 0; i < size; i++) {
		t = a[i];
		a[i] = b[i];
		b[i] = t;
	}
}

void quick_sort(int arr[][2], int low, int high) {
	if (low < high) {
		int pivot = arr[high][1];
		int k = low - 1;

		for (int i = low; i < high; i++) {
			if (arr[i][1] > pivot) {
				k++;
				swap_rows(arr[i], arr[k], 2);
			}
		}

		k++;
		swap_rows(arr[k], arr[high], 2);
		quick_sort(arr, low, k - 1);
		quick_sort(arr, k + 1, high);
	}
}

int main() {
	int N;
	cin >> N;

	int freq[N][2];
	for (int i = 0; i < N; i++) {
		freq[i][0] = i + 1;
		cin >> freq[i][1];
		
	}
	if (N == 1) {
		for (int i = 0; i < freq[0][1]; i++) cout << 1 << ' ';
		cout << endl;
		return 0;
	}

	quick_sort(freq, 0, N - 1);
	int pos = 1;
	while (freq[0][1] > 0) {
		cout << freq[0][0] << ' ';
		freq[0][1]--;

		int k = 1;
		while (k < N && freq[k][1] == 0) k++;
		
		if (k == N) continue;
		cout << freq[k][0] << ' ';
		freq[k][1]--;


		for (int i = 1; i < N; i++) {
			if (freq[i][1] == freq[0][1] + 1) {
				cout << freq[i][0] << ' ';
				freq[i][1]--;
			}
		}

	}
	cout << endl;
	return 0;
}
