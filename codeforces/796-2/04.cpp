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
        long long n, k;
        std::cin >> n >> k;

        // We 100% collect every mushroom which was there at 0-minute
        // and now need to minimize what will be left after us
        if (k >= n) {
            long long sum = 0;
            for (int j = 0; j < n; j++) {
                long long a;
                std::cin >> a;
                sum += a;
            }

            std::cout << (sum + (k-1) * n - (n * (n-1)) / 2) << '\n';
        }
        // Find how many 0-minute mushrooms we can collect at max
        // by searching for greatest sum in k-length subsequence
        else {
            std::vector<long long> a(n, 0);
            long long sum = 0;
            for (int j = 0; j < k; j++) {
                std::cin >> a[j];
                sum += a[j];
            }

            long long max_sum = sum;
            for (int j = k; j < n; j++) {
                std::cin >> a[j];
                sum += a[j] - a[j-k];
                max_sum = std::max(sum, max_sum);
            }

            std::cout << (max_sum + (k * (k-1)) / 2) << '\n';
        }
    }
}
