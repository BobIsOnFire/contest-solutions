#include <bits/stdc++.h>
#include <math.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, s = 0;
	cin >> N;

	int weights[N];
	for (int i = 0; i < N; i++) {
		cin >> weights[i];
		s += weights[i];
	}

	int size = s / 2, k = pow(2, N), max = 0;

	for (int i = 0; i < k; i++) {
		int sum = 0;
		int mask = i;
		int j = 0;
		while (mask > 0) {
			if ((mask & 1) == 1) sum += weights[j];
			j++;
			mask >>= 1;
		}

		if (sum > max && sum <= size) max = sum;
	}

	cout << (s - 2 * max) << endl;
}
