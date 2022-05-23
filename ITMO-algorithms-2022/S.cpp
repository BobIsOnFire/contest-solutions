#include <bits/stdc++.h>

struct square {
    int val = -1;
    int horiz_idx = -1;
    int vert_idx = -1;
    bool visited = false;
};

struct matrix_vector {
    int height;
    int width;
    std::vector<square> data;

    matrix_vector(int N, int M) {
        height = N;
        width = M;
        data = std::vector<square>(N * M, square {});
    }

    square& at(int i, int j) {
        return data[i * width + j];
    }
};

void fill_palyndromic(matrix_vector& matrix, std::vector<square*> &squares, int i, int j) {
    bool horiz = true;
    while (true) {
        square &s = matrix.at(i, j);
        
        if (s.visited) break;

        s.visited = true;
        squares.push_back(&s);

        if (horiz) {
            if (s.horiz_idx < 0) break;
            j = s.horiz_idx;
        } else {
            if (s.vert_idx < 0) break;
            i = s.vert_idx;
        }

        horiz = !horiz;
    }
}

int find_closest(std::vector<square*> &squares) {
    int count[10] = {0};
    for (square *st : squares) {
        count[st->val]++;
    }

    int total_up = 0;
    int diff = 0;
    for (int i = 1; i < 10; i++) {
        total_up += count[i];
        diff += i * count[i];
    }

    int min_idx = 0;
    int min_val = diff;

    int total_down = count[0];

    for (int i = 1; i < 10; i++) {
        diff -= total_up;
        diff += total_down;

        total_up -= count[i];
        total_down += count[i];

        if (diff < min_val) {
            min_idx = i;
            min_val = diff;
        }
    }

    return min_idx;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int N, M;
    std::cin >> N >> M;

    matrix_vector matrix(N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char ch;
            std::cin >> ch;
            if (ch != '.') matrix.at(i, j).val = ch - '0';
        }
    }

    int i = 0, j = 0;
    while (i < N) {
        // Looking for horizontal word..
        while (j < M && matrix.at(i, j).val < 0) j++;
        
        // End of row reached
        if (j == M) {
            i++;
            j = 0;
            continue;
        }

        // Found start of a word, looking for its end
        int start = j, end = j;
        while (end < M && matrix.at(i, end).val >= 0) end++;
        j = end;
        end--;

        while (start < end) {
            matrix.at(i, start).horiz_idx = end; 
            matrix.at(i, end).horiz_idx = start;
            start++, end--; 
        }
    }

    i = 0, j = 0;
    while (j < M) {
        // Looking for vertical word..
        while (i < N && matrix.at(i, j).val < 0) i++;
        
        // End of column reached
        if (i == N) {
            j++;
            i = 0;
            continue;
        }

        // Found start of a word, looking for its end
        int start = i, end = i;
        while (end < N && matrix.at(end, j).val >= 0) end++;
        i = end;
        end--;

        while (start < end) {
            matrix.at(start, j).vert_idx = end; 
            matrix.at(end, j).vert_idx = start;
            start++, end--; 
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            square &s = matrix.at(i, j);
            if (s.visited || s.val < 0) continue;
            
            std::vector<square*> squares;
            fill_palyndromic(matrix, squares, i, j);

            int vert = s.vert_idx;
            if (vert >= 0 && !matrix.at(vert, j).visited)
                fill_palyndromic(matrix, squares, vert, j);
            
            int closest = find_closest(squares);
            for (square *st : squares) st->val = closest;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            square &s = matrix.at(i, j);
            if (s.val < 0) std::cout << '.';
            else std::cout << s.val;
        }
        std::cout << '\n';
    }
}
