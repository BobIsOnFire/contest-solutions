#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    std::vector<std::unordered_set<int>> groups;

    int N;
    std::cin >> N;

    unsigned long long count = 0;
    for (int i = 0; i < N; i++) {
        int a;
        std::cin >> a;
        
        groups.emplace_back();
        for (auto &group : groups) {
            int val = a;

            std::unordered_set<int>::const_iterator iter;
            while ((iter = group.find(val)) != group.end()) {
                group.erase(iter);
                val++;
            }

            if (group.empty()) count++;
            group.insert(val);
        }
    }

    std::cout << count;
}
