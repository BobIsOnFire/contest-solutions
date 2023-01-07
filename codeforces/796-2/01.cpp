#include <bits/stdc++.h>

#ifdef CONTEST_DEBUG
#  define dbg(x) std::cout << x
#else
#  define dbg(x)
#endif

inline constexpr int max_pow2(int c) {
    int i = 1;
    while (c % 2 == 0) {
        c >>= 1;
        i <<= 1;
    }
    return i;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; i++) {
        int c;
        std::cin >> c;

        if (c == 1) std::cout << "3\n";
        else {
            int i = max_pow2(c);
            if (i == c) {
                std::cout << (i+1) << '\n';
            }
            else std::cout << i << '\n';
        }
    }
}
