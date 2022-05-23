#include <bits/stdc++.h>

bool is_enough(std::vector<int> &stables, int count, int x) {
    int last = stables[0];
    int cows = 1;
    for (int s : stables) {
        if (s - last >= x) {
            cows++;
            last = s;
        }
    }
    // std::cout << x << ": " << (cows >= count) << "\n";
    return cows >= count;
}

int find_max(std::vector<int> &stables, int count, int lo, int hi) {
    while (lo != hi) {
        // std::cout << lo << " " << hi << "?\n";
        int mid = (lo + hi) / 2 + 1;
        if (is_enough(stables, count, mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    return lo;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> stables(N, 0);

    for (int i = 0; i < N; i++) {
        std::cin >> stables[i];
    }

    std::cout << find_max(stables, M, 0, stables.back() - stables.front());
}
