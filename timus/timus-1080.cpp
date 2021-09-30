#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    int adjacency[N][N];
    int colors[N];

    for (int i = 0; i < N; i++) {
        colors[i] = -1;
        for (int j = 0; j < N; j++) adjacency[i][j] = 0;
    }

    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        while (a > 0) {
            adjacency[i][a - 1] = 1;
            adjacency[a - 1][i] = 1;
            cin >> a;
        }
    }

    int queue[N];
    for (int i = 0; i < N; i++) {
        if (colors[i] > -1) continue;

        int h = 0, t = 0;
        queue[t++] = i;
        colors[i] = 0;

        while (h < t) {
            int from = queue[h++];
            for (int to = 0; to < N; to++) {
                if (adjacency[from][to] == 0) continue;
                if (colors[to] == colors[from]) {
                    cout << -1 << "\n";
                    return 0;
                }

                if (colors[to] == -1) {
                    colors[to] = 1 - colors[from];
                    queue[t++] = to;
                }
            }
        }
    }

    for (int i = 0; i < N; i++) cout << colors[i];
    cout << "\n";
    return 0;
}