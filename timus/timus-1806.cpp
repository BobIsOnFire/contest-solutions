#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

struct soldier {
    int min_path = 2000000000;
    int from = -1;
    long long number;
} soldiers[50000];

int c_nodes[135];
int c_weights[135];

long long power[10];
int weights[10];

unordered_map<long long, int> numbers;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    for (int i = 0; i < 10; i++) cin >> weights[i];

    for (int i = 0; i < N; i++) {
        long long number;
        cin >> number;
        numbers[number] = i;
        soldiers[i].number = number;
    }

    power[9] = 1;
    for (int i = 8; i >= 0; i--) power[i] = power[i + 1] * 10;

    soldiers[0].min_path = 0;
    set<pair<int, int>> queue; // p.first is soldier.min_path, p.second is his index
    queue.insert({0, 0});

    while (!queue.empty()) {
        auto next = queue.begin();
        pair<int, int> from = *next;
        if (from.second == N - 1) break;
        queue.erase(next);

        int k = 0;
        long long number = soldiers[from.second].number;
        long long compare = number;

        for (int i = 0; i < 10; i++) {
            int digit = number / power[i] % 10;
            compare -= digit * power[i];
            for (int j = 0; j < 10; j++) {
                if (j == digit) continue;

                auto it = numbers.find(compare + j * power[i]);
                if (it != numbers.end()) {
                    int index = (*it).second;
                    c_nodes[k++] = index;
                    c_weights[k++] = weights[i];
                }
            }

            for (int j = i + 1; j < 10; j++) {
                int n_digit = number / power[j] % 10;
                if (digit == n_digit) continue;
                compare -= n_digit * power[j];

                auto it = numbers.find(compare + n_digit * power[i] + digit * power[j]);
                if (it != numbers.end()) {
                    int index = (*it).second;
                    c_nodes[k++] = index;
                    c_weights[k++] = weights[i];
                }

                compare += n_digit * power[j];
            }

            compare += digit * power[i];
        }

        for (int i = 0; i < k; i++) {
            int min_path = soldiers[c_nodes[i]].min_path;
            int new_path = from.first + c_weights[i];
            if (min_path > new_path) {
                soldiers[c_nodes[i]].min_path = new_path;
                soldiers[c_nodes[i]].from = from.second;
                queue.erase({min_path, c_nodes[i]});
                queue.insert({new_path, c_nodes[i]});
            }
        }
    }

    if (soldiers[N - 1].from == -1) {
        cout << "-1\n";
        return 0;
    }

    int chain[N];
    int pointer = 0;
    chain[pointer++] = N;

    int k = N - 1;
    while (k != 0) {
        k = soldiers[k].from;
        chain[pointer++] = k + 1;
    }

    cout << soldiers[N - 1].min_path << "\n";
    cout << pointer << "\n";
    for (int i = pointer - 1; i >= 0; i--) cout << chain[i] << " ";
    cout << "\n";
}