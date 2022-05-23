#include <bits/stdc++.h>

bool pair(char &ch1, char &ch2) {
    return ch1 - 'A' == ch2 - 'a' || ch1 - 'a' == ch2 - 'A';
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    std::string line;
    std::cin >> line;

    std::vector<int> pairs (line.length(), -1);

    for (int i = 0; i < line.length(); i++) {
        // (j,i), j<i is a pair if:
        // 1. pairs[j] == -1
        // 2. pairs[k] != -1 for all j < k < i
        // 3. pair(line[i], line[j]) == true

        int j = i-1;

        while (j >= 0 && pairs[j] != -1) j = pairs[j] - 1;

        if (j < 0) {
            // print "Impossible" and exit?
            continue;
        }

        if (pair(line[i], line[j])) {
            pairs[i] = j;
            pairs[j] = i;
        }
    }

    for (auto i: pairs) {
        if (i == -1) {
            std::cout << "Impossible\n";
            return 0;
        }
    }

    std::cout << "Possible\n";

    int index = 0;
    for (int i = 0; i < pairs.size(); i++) {
        if (line[i] >= 'a' && line[i] <= 'z') {
            pairs[pairs[i]] = index++;
        }
    }

    for (int i = 0; i < pairs.size(); i++) {
        if (line[i] >= 'A' && line[i] <= 'Z') {
            std::cout << (pairs[i] + 1) << " ";
        }
    }
    std::cout << "\n";
}
