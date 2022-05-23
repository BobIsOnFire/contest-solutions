#include <algorithm>
#include <bits/stdc++.h>

struct matrix_vector {
    int m_size;
    std::vector<int> m_data;

    matrix_vector(int N) {
        m_size = N;
        m_data = std::vector<int>(N * N, 0);
    }

    int& at(int i, int j) {
        return m_data[i * m_size + j];
    }

    int max_element() {
        return *std::max_element(m_data.begin(), m_data.end());
    }

    int size() {
        return m_size;
    }
};

void do_dfs(matrix_vector &matrix, int max_cost, std::vector<bool> &visited, int current) {
    visited[current] = true;
    for (int i = 0; i < matrix.size(); i++) {
        if (!visited[i] && matrix.at(current, i) <= max_cost) {
            do_dfs(matrix, max_cost, visited, i);
        }
    }
}

void do_dfs_transposed(matrix_vector &matrix, int max_cost, std::vector<bool> &visited, int current) {
    visited[current] = true;
    for (int i = 0; i < matrix.size(); i++) {
        if (!visited[i] && matrix.at(i, current) <= max_cost) {
            do_dfs_transposed(matrix, max_cost, visited, i);
        }
    }
}

bool is_strongly_connected(matrix_vector &matrix, int max_cost, std::vector<bool> &visited) {
    visited.assign(matrix.size(), false);
    do_dfs(matrix, max_cost, visited, 0);
    for (bool v : visited) if (!v) return false;

    visited.assign(matrix.size(), false);
    do_dfs_transposed(matrix, max_cost, visited, 0);
    for (bool v : visited) if (!v) return false;

    return true;
}

int find_solution(matrix_vector &matrix, int lo, int hi) {
    std::vector<bool> visited(matrix.size(), false);
    while (lo != hi) {
        // std::cout << lo << " " << hi << "?\n";
        int mid = (lo + hi) / 2;
        if (is_strongly_connected(matrix, mid, visited)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    return lo;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int N;
    std::cin >> N;

    matrix_vector matrix(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> matrix.at(i, j);
        }
    }

    std::cout << find_solution(matrix, 0, matrix.max_element());
}
