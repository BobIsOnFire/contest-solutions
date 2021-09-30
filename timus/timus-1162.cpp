#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct currency {
    double amount = -1;
    vector<pair<int, pair<double, double>>> operations;
} currencies[100];

bool dfs(int from, int depth = 0) {
    for (pair<int, pair<double, double>> op : currencies[from].operations) {
        int to = op.first;
        double value = (currencies[from].amount - op.second.second) * op.second.first;
        
        if (value <= 0) continue;
        if (currencies[to].amount != -1) {
            if (currencies[to].amount + 0.000001 < value) return true;
            continue;
        }
        
        currencies[to].amount = value;
        if (dfs(to, depth + 1)) return true;
        currencies[to].amount = -1;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, S;
    double V;
    cin >> N >> M >> S >> V;

    int op_count = 0;
    for (int i = 0; i < M; i++) {
        int a, b;
        double rab, cab, rba, cba;
        cin >> a >> b >> rab >> cab >> rba >> cba;

        currencies[a - 1].operations.push_back({b - 1, {rab, cab}});
        currencies[b - 1].operations.push_back({a - 1, {rba, cba}});
    }

    currencies[S - 1].amount = V;

    if (dfs(S - 1)) cout << "YES\n";
    else cout << "NO\n";
}