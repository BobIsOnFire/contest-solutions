#include <bits/stdc++.h>

#ifdef CONTEST_DEBUG
#  define dbg(x) std::cout << x
#else
#  define dbg(x)
#endif

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    std::vector<int> nums (N, 0);
    for (int i = 0; i < N; i++) {
        std::cin >> nums[i];
    }

    std::sort(nums.begin(), nums.end());

    int max_run = 0;
    for (int i = 1; i < N-1; i++) {
        int prev = nums[i] - nums[i-1];
        int next = nums[i+1] - nums[i];
        if (prev == next) {
            max_run = std::max(max_run, prev);
        }
    }

    std::cout << max_run;
}
