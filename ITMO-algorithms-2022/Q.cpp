#include <bits/stdc++.h>

struct matrix_vector {
    int height;
    int width;
    std::vector<int> data;

    matrix_vector(int N, int M) {
        height = N;
        width = M;
        data = std::vector<int>(N * M, 0);
    }

    int& at(int i, int j) {
        return data[i * width + j];
    }

    int entropy(int i, int j) {
        int other_i = height - i - 1;
        int other_j = width - j - 1;

        if (other_i == i && other_j == j) return 0;
        if (other_i == i) {
            return at(i, j) != at(i, other_j);
        }
        if (other_j == j) {
            return at(i, j) != at(other_i, j);
        }

        std::array<int, 4> nums = {at(i, j), at(other_i, j), at(i, other_j), at(other_i, other_j)};
        std::sort(nums.begin(), nums.end());

        int distinct = 1;
        for (int k = 1; k < 4; k++) {
            if (nums[k] != nums[k-1]) distinct++;
        }

        switch(distinct) {
            case 1:
                return 0;
            case 2:
                if (nums[1] == nums[2]) return 1;
                else return 2;
            case 3:
                return 2;
            default:
                return 3;
        }
    }
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int N, M;
    std::cin >> N >> M;

    matrix_vector matrix(N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> matrix.at(i, j);
        }
    }

    int count = 0;
    for (int i = 0; i < (N+1)/2; i++) {
        for (int j = 0; j < (M+1)/2; j++) {
            count += matrix.entropy(i, j);
        }
    }

    std::cout << count;
}