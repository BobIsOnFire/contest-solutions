#include <bits/stdc++.h>

#ifdef CONTEST_DEBUG
#  define dbg(x) std::cout << x
#else
#  define dbg(x)
#endif

#define MODULO 1000000007

int saws[14] = {0, 1, 1, 2, 5, 16, 61, 272, 1385, 7936, 50521, 353792, 2702765, 22368256};
int cache[101][14] = {{0}};

long long get_combinations(int n, int size) {
    if (cache[n][size]) return cache[n][size];

    if (n * 2 < size * (size+1)) return 0;

    if (size == 1) {
        cache[n][size] = 1;
        return 1;
    }

    if (size == 2) {
        cache[n][size] = (n+1) / 2 - 1;
        return cache[n][size];
    }


    cache[n][size] = get_combinations(n - size, size - 1) + get_combinations(n - size, size);
    return cache[n][size];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    long long total = 0;
    for (int i = 1; i <= 13; i++) {
        total += (get_combinations(N, i) * saws[i]) % MODULO;
    }

    std::cout << (total % MODULO);
}

