#include <iostream>
using namespace std;

int main() {
	int N;
	cin >> N;

	char heads[5 * N], misc[5 * N];

	cin >> heads;
	cin >> misc;
	cin >> misc;
	
	int k = -1;
	int num = 0;

	int half_left = 0;
	int half_right = 0;
	int even_left = 0;
	int even_right = 0;
	while (heads[++k] != 0) {
		if (heads[k] != 64) continue;
		bool left = heads[k - 1] == 60;
		num++;

		if (num <= N / 2) {
			if (left) half_right++;
			else half_left++;
		} else {
			if (left) half_left++;
			else half_right++;
		}

		if (num % 2 == 0) {
			if (left) even_right++;
			else even_left++;
		} else {
			if (left) even_left++;
			else even_right++;
		}
	}

	cout << min(min(half_left, half_right), min(even_left, even_right)) << "\n";
}

