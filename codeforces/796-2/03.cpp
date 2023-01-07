#include <bits/stdc++.h>

#ifdef CONTEST_DEBUG
#  define dbg(x) std::cout << x
#else
#  define dbg(x)
#endif

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        std::cin >> n;

        int letters[128] = {0};
        for (int j = 0; j < n+n+1; j++) {
            std::string s;
            std::cin >> s;
            for (char ch : s) {
                letters[int(ch)]++;
            }
        }

        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (letters[int(ch)] % 2 != 0) std::cout << ch << '\n';
        }
    }
}
