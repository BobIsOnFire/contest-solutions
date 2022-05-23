#include <bits/stdc++.h>

#ifdef CONTEST_DEBUG
#  define dbg(x) std::cout << x
#else
#  define dbg(x)
#endif

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    size_t N; int M;
    std::cin >> N >> M;

    std::vector<std::array<int, 3>> results;

    for (int x1 = -M; x1 <= M; x1++) {
        if (x1 == 0) continue;

        int abs_mx1 = std::abs(M / x1);
        int start = std::max(-M - x1, -abs_mx1);
        int end = std::min(M - x1, abs_mx1);

        for (int x2 = start; x2 <= end; x2++) {
            if (x2 == 0 || x2 == -x1 || x2 == x1) continue;

            int a_s = 1;
            int b_s = -x1 - x2;
            int c_s = x1 * x2;

            int a = a_s, b = b_s, c = c_s;
            while (abs(b) <= M && abs(c) <= M) {
                results.push_back({a, b, c});
                results.push_back({-a, -b, -c});
                a += a_s;
                b += b_s;
                c += c_s;
                if (results.size() >= N) break;
            }
            if (results.size() >= N) break;
        }
        if (results.size() >= N) break;
    }

    if (results.size() < N) {
        std::cout << "NO\n";
        return 0;
    }

    std::cout << "YES\n";
    for (size_t i = 0; i < N; i++) {
        std::cout << results[i][0] << " " << results[i][1] << " " << results[i][2] << "\n";
    }
}
