#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct edge_t {
    int weight;
    int a;
    int b;
} edges[15000];

int get_parent(int node, int parents[]) {
    if (node == parents[node]) return node;
    parents[node] = get_parent(parents[node], parents);
    return parents[node];
}

void link_parents(int node1, int node2, int parents[]) {
    node1 = get_parent(node1, parents);
    node2 = get_parent(node2, parents);
    if (rand() & 1) swap(node1, node2);
    if (node1 != node2) parents[node1] = node2;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i].a = a - 1;
        edges[i].b = b - 1;
        edges[i].weight = c;
    }

    sort(edges, edges + M, [] (const edge_t& edge1, const edge_t& edge2) { return edge1.weight < edge2.weight; });
    int parents[N];
    for (int i = 0; i < N; i++) parents[i] = i;

    edge_t* tree[N - 1];
    int k = 0;
    int max = 0;
    for (int i = 0; i < M; i++) {
        int a = edges[i].a;
        int b = edges[i].b;

        if (get_parent(a, parents) != get_parent(b, parents)) {
            max = edges[i].weight;
            tree[k++] = &edges[i];
            link_parents(a, b, parents);
        }
    }

    cout << max << "\n";
    cout << (N - 1) << "\n";
    for (edge_t* e : tree) {
        cout << (e->a + 1) << " " << (e->b + 1) << "\n";
    }
}