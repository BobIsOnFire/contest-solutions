#include <iostream>
#include <unordered_map>

struct result {
    int value;
    int count;
    bool has_same;
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::unordered_map<int, int> mapper;

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;
        mapper[num]++;
    }

    result first = {-1, 0, true};
    result second = {-1, 0, true};

    for (auto & m : mapper) {
        result current = {m.first, m.second, false};
        if (current.count > first.count) {
            second = first;
            first = current;
            continue;
        }

        if (current.count == first.count) {
            first.has_same = true;
            continue;
        }

        if (current.count > second.count) {
            second = current;
            continue;
        }

        if (current.count == second.count) {
            second.has_same = true;
            continue;
        }
    }

    if (first.has_same || second.has_same) std::cout << "-1\n";
    else std::cout << second.value << "\n";
}
