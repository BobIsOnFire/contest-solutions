#include <array>
#include <iostream>

struct Results {
    constexpr Results(): table() {
        table[0] = 0;
        for (int i = 1; i < 10000; i++) {
            int nums[] = { i, (i / 10), (i / 100), (i / 1000) };

            if ( nums[0] % 10 == 1 || nums[1] % 10 == 1 || nums[2] % 10 == 1 || nums[3] % 10 == 1 ) {
                table[i] = table[i-1] + 1;
            } else {
                table[i] = table[i-1];
            }
        }

        table[10000] = table[9999] + 1;
    }
    
    int table[10001];
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int lo, hi;
    std::cin >> lo >> hi;

    constexpr auto res = Results();

    std::cout << res.table[hi] - res.table[lo - 1];
}
