#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct node_t {
    vector<pair<int, int>> children;
} nodes[500];

void sort_nodes(int index, vector<int> *sorted, bool visited[]) {
    visited[index] = true;
    for (pair<int, int> child : nodes[index].children) {
        if (visited[child.first]) continue;
        sort_nodes(child.first, sorted, visited);
    }
    sorted->push_back(index);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        nodes[a - 1].children.push_back({b - 1, c});
    }

    vector<int> sorted;
    bool visited[N];
    for (int i = 0; i < N; i++) visited[i] = false;

    int S, F;
    cin >> S >> F;

    sort_nodes(S - 1, &sorted, visited);
    int max_path[N];
    for (int i = 0; i < N; i++) max_path[i] = -1;
    max_path[S - 1] = 0;
    
    for (int i = sorted.size() - 1; i >= 0 && sorted[i] != F - 1; i--) {
        int index = sorted[i];
        for (pair<int, int> p : nodes[index].children) {
            max_path[p.first] = max(max_path[p.first], max_path[index] + p.second);
        }
    }

    if (max_path[F - 1] < 0) cout << "No solution\n";
    else cout << max_path[F - 1] << "\n";
}