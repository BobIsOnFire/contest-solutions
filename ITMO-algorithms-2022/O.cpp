#include <bits/stdc++.h>

struct bitmatrix {
    std::vector<uint64_t> nums;
    int page;

    bitmatrix(std::size_t N) {
        page = N;
        int size = N * N;
        nums = std::vector<uint64_t>(size / 64 + 1, 0);
    }

    bool get(std::size_t i, std::size_t j) const {
        int idx = i * page + j;
        return (nums[idx / 64] & (1UL << (idx % 64))) != 0;
    }

    void set(std::size_t i, std::size_t j, bool v) {
        int idx = i * page + j;
        uint64_t mask = 1UL << (idx % 64);
        if (v) {
            nums[idx / 64] |= mask;
        } else {
            nums[idx / 64] &= ~mask;
        }
    }
};

bool dfs_colorize(bitmatrix &matrix, int *colors, int N, int i, int color) {
    if (colors[i] != 0) return true;

    colors[i] = color;
    for (int j = 0; j < N; j++) {
        if (!matrix.get(i, j)) continue;

        if (colors[j] == 0) {
            if (!dfs_colorize(matrix, colors, N, j, 3 - color)) return false;
            continue;
        }

        if (colors[i] == colors[j]) return false;
    }

    return true;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);


    int N, M;
    std::cin >> N >> M;

    bitmatrix matrix(N);

    for (int i = 0; i < M; i++) {
        int from, to;
        std::cin >> from >> to;

        if (from > to) std::swap(from, to);
        matrix.set(from-1, to-1, true);
        matrix.set(to-1, from-1, true);
    }

    int colors[100] = {0};
    for (int i = 0; i < N; i++) {
        if (colors[i] != 0) continue;
        if (!dfs_colorize(matrix, colors, N, i, 1)) {
            std::cout << "NO\n";
            return 0;
        }
    }

    std::cout << "YES\n";
}
