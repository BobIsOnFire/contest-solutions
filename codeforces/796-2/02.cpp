#include <bits/stdc++.h>

#ifdef CONTEST_DEBUG
#  define dbg(x) std::cout << x
#else
#  define dbg(x)
#endif

inline constexpr int max_pow2(int c) {
    int i = 0;
    while (c % 2 == 0) {
        c >>= 1;
        i += 1;
    }
    return i;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        std::cin >> n;

        int min_pow = INT_MAX;
        int count = 0;
        for (int j = 0; j < n; j++) {
            int a;
            std::cin >> a;

            if (a % 2 == 0) {
                count++;
                min_pow = std::min(min_pow, max_pow2(a));
            }
        }

        // 1. At least one odd number - use `count` operations to sum up every even number with it
        // 2. Otherwise, create an odd number with `min_pow` ops and sum it up with `count-1` even nums left
        if (count != n) std::cout << count << '\n';
        else std::cout << (min_pow + count - 1) << '\n';
    }
}
