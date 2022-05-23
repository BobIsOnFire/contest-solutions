#include <bits/stdc++.h>

#ifdef CONTEST_DEBUG
#  define dbg(x) std::cout << x << "\n"
#else
#  define dbg(x)
#endif

long long get_paths(int adjacency[20][20], bool visited[20], int from, int to, int c_from, int c_to, bool found, int p) {
    if (from == to) return int(found);
    visited[from] = true;

    int paths = 0;
    for (int i = 0; i < 20; i++) {
        if (adjacency[from][i] == 0) continue;
        if (visited[i]) continue;
        
        bool child_found = found || (c_from == from && c_to == i) || (c_from == i && c_to == from);
        dbg((from+1) << " " << (i+1) << " found: " << child_found);
        paths += adjacency[from][i] * get_paths(adjacency, visited, i, to, c_from, c_to, child_found, p);
    }

    visited[from] = false;
    dbg((from+1) << " paths: " << paths);
    return paths % p;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, M, a, b, c, p;
    std::cin >> N >> M >> a >> b >> c >> p;

    int adjacency[20][20] = {{0}};
    bool visited[20] = {0};

    int c_from, c_to;

    for (int i = 0; i < M; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adjacency[u][v]++;
        adjacency[v][u]++;

        if (i == c-1) {
            c_from = u;
            c_to = v;
        }
    }

    dbg("Looking for " << (c_from+1) << " " << (c_to+1));
    adjacency[c_from][c_to] = 1;
    adjacency[c_to][c_from] = 1;

    std::cout << (get_paths(adjacency, visited, a-1, b-1, c_from, c_to, false, p) % p);
}
