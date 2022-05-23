#include <bits/stdc++.h>

struct range {
    int from;
    int to;

    bool operator<(const range &other) const {
        return (to - from) < (other.to - other.from);
    }
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;
	
	if (N < 3) {
		std::cout << 1 << ' ' << N;
        return 0;
    }

    std::pair<int, int> prev;
    std::cin >> prev.first >> prev.second;

	range cur_range {1, 2};
	range max_range {0, 0};
	
	for (int i = 2; i < N; i++) {
        int a;
        std::cin >> a;

        if (a == prev.first && a == prev.second) {
            max_range = std::max(max_range, cur_range);
            cur_range = {i, i+1};
        } else {
            prev.first = prev.second;
            prev.second = a;
            cur_range.to++;
        }
    }
	
    max_range = std::max(max_range, cur_range);

    std::cout << max_range.from << ' ' << max_range.to;
    return 0;
}
