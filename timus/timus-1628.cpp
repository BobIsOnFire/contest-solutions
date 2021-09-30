#include <bits/stdc++.h>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int m, n, k;
	cin >> m >> n >> k;

	pair<int, int> dots[k + 2];
	dots[0] = {1, 0};
	dots[k + 1] = {m, n + 1};

	for (int i = 1; i <= k; i++) {
		int a, b;
		cin >> a >> b;
		dots[i] = {a, b};
	}

	sort(dots, dots + k + 2);
	
	int counter = 0;
	int block_counter = 0;
	set<pair<int, int>> blocks;

	for (int i = 1; i <= k + 1; i++) {
		int first = dots[i].first - dots[i - 1].first;
		int second = dots[i].second - dots[i - 1].second;

		if (first == 0) {
			if (second == 1) continue;
			if (second == 2) {
				block_counter++;
				blocks.insert({dots[i].first, dots[i].second - 1});
				continue;
			}

			counter++;
			continue;
		}

		if (n > 1) counter += first - 1;

		if (dots[i - 1].second < n) {
			if (dots[i - 1].second == n - 1) {
				block_counter++;
				blocks.insert({dots[i - 1].first, n});
			} else counter++;
		}

		if (dots[i].second > 1) {
			if (dots[i].second == 2) {
				block_counter++;
				blocks.insert({dots[i].first, 1});
			} else counter++;
		}
	}

	dots[0] = {0, 1};
	dots[k + 1] = {m + 1, n};

	sort(dots, dots + k + 2, 
			[](pair<int, int> a, pair<int, int> b) {
				if (a.second != b.second) return a.second < b.second;
				return a.first < b.first;
			}
	);

	for (int i = 1; i <= k + 1; i++) {
		int first = dots[i].first - dots[i - 1].first;
		int second = dots[i].second - dots[i - 1].second;

		if (second == 0) {
			if (first == 1) continue;
			if (first == 2) {
				block_counter++;
				blocks.insert({dots[i].first - 1, dots[i].second});
				continue;
			}

			counter++;
			continue;
		}

		if (m > 1) counter += second - 1;

		if (dots[i - 1].first < m) {
			if (dots[i - 1].first == m - 1) {
				block_counter++;
				blocks.insert({m, dots[i - 1].second});
			} else counter++;
		}

		if (dots[i].first > 1) {
			if (dots[i].first == 2) {
				block_counter++;
				blocks.insert({1, dots[i].second});
			} else counter++;
		}
	}

	counter += block_counter - blocks.size();
	cout << counter << '\n';	

	return 0;
}
