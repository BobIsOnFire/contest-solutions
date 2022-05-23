#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int N, K;
    std::cin >> N >> K;

    int counting_sort[10001] = {0};
    int sum = 0;

    for (int i = 0; i < N; i++) {
        int a;
        std::cin >> a;

        counting_sort[a]++;
        sum += a;
    }

    int idx = 0;
    for (int i = 10000; i > 0; i--) {
        idx += counting_sort[i];
        sum -= i * (idx / K);
        idx %= K;
    }

    std::cout << sum;
}