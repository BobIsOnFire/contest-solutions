#include <bits/stdc++.h>

#ifdef CONTEST_DEBUG
#  define dbg(x) std::cout << x
#else
#  define dbg(x)
#endif

struct Dominance {
    int dominants_count[100001] = {0};

    constexpr Dominance() {
        int count = 0;
        for (int i = 1; i <= 100000; i++) {
            dominants_count[i] = count;
            int a = 0;
            int num = i;
            while (num % 2 == 0) {
                num /= 2;
                a++;
            }

            int b = 0;
            while (num % 3 == 0) {
                num /= 3;
                b++;
            }

            if (b > a) count++;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;
    std::cout << Dominance().dominants_count[N];
}
