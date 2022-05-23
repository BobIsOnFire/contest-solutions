#include <bits/stdc++.h>

#define PLAIN '.'
#define FOREST 'W'
#define WATER '#'

struct coord {
    int i;
    int j;

    coord operator--(int) {
        i--;
        j--;
        return *this;
    }

    bool operator==(coord other) {
        return i == other.i && j == other.j;
    }

    coord up() {
        return {i-1, j};
    }

    coord down() {
        return {i+1, j};
    }

    coord left() {
        return {i, j-1};
    }

    coord right() {
        return {i, j+1};
    }

    char to(coord to) {
        if (to == up()) return 'N';
        if (to == down()) return 'S';
        if (to == left()) return 'W';
        if (to == right()) return 'E';
        return '?';
    }
};

struct tile {
    char terrain;
    bool visited;
    char direction;
    coord from;
};

struct tile_map {
    int height;
    int width;
    std::vector<tile> data;

    tile& operator[](coord c) {
        return data[c.i * width + c.j];
    }
};

void check_and_push(tile_map &map, std::vector<std::pair<coord, coord>> &plain, std::vector<std::pair<coord, coord>> &forest, coord from, coord to) {
    if (map[to].visited) return;
    if (map[to].terrain == PLAIN) plain.push_back({from, to});
    if (map[to].terrain == FOREST) forest.push_back({from, to});
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int N, M;
    coord begin, end;
    std::cin >> N >> M >> begin.i >> begin.j >> end.i >> end.j;

    begin--; end--;

    tile_map map {N, M, std::vector<tile>(N * M, tile{})};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> map[{i, j}].terrain;
        }
    }

    std::vector<std::pair<coord, coord>> current, one_step, two_step;
    one_step.push_back({{}, begin});

    bool found = false;
    int count = 0;

    while (!found && (!one_step.empty() || !two_step.empty())) {
        current = std::move(one_step);
        one_step = std::move(two_step);
        two_step = {};

        for (std::pair<coord, coord> p: current) {
            coord prev = p.first;
            coord c = p.second;

            if (map[c].visited) continue;

            map[c].visited = true;
            map[c].from = prev;
            map[c].direction = prev.to(c);

            if (c == end) {
                found = true;
                break;
            }

            if (c.i > 0) check_and_push(map, one_step, two_step, c, c.up());
            if (c.i < N - 1) check_and_push(map, one_step, two_step, c, c.down());
            if (c.j > 0) check_and_push(map, one_step, two_step, c, c.left());
            if (c.j < M - 1) check_and_push(map, one_step, two_step, c, c.right());
        }

        count++;
    }

    if (!found) {
        std::cout << "-1\n";
        return 0;
    }

    count--;
    std::cout << count << "\n";

    int k = 0;
    for (coord cur = end; !(cur == begin); cur = map[cur].from) k++;

    std::string res(k, ' ');

    for (coord cur = end; !(cur == begin); cur = map[cur].from) {
        res[--k] = map[cur].direction;
    }

    std::cout << res << "\n";
}
