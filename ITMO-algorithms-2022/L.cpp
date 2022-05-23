#include <bits/stdc++.h>

struct number {
    int index;
    int value;
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int N, K;
    std::cin >> N >> K;

    std::deque<number> window;
    for (int i = 0; i < N; i++) {
        number num {i, 0};
        std::cin >> num.value;

        while (!window.empty() && num.index - window.front().index > K - 1) window.pop_front();
        while (!window.empty() && num.value < window.back().value) window.pop_back();
        window.push_back(num);

        if (i >= K-1) std::cout << window.front().value << " ";
    }
}