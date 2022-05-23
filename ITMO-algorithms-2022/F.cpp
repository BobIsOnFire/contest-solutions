#include <bits/stdc++.h>

#include <string>
#include <vector>

struct concat_view {
    const std::string &s1;
    const std::string &s2;

    std::size_t length() const {
        return s1.length() + s2.length();
    }

    const char & operator[] (std::size_t i) const {
        if (i < s1.length()) return s1[i];
        return s2[i - s1.length()];
    }
};

bool comparator(const std::string &s1, const std::string &s2) {
    const concat_view c1 {s1, s2};
    const concat_view c2 {s2, s1};

    int i = 0;
    while (i < c1.length() && c1[i] == c2[i]) i++;
    return c1[i] > c2[i];
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    std::vector<std::string> pieces;
    while (!std::cin.eof()) {
        pieces.emplace_back();
        std::cin >> pieces.back();
        if (pieces.back().empty()) pieces.pop_back();
    }

    std::sort(pieces.begin(), pieces.end(), comparator);
    for (const auto &p : pieces) std::cout << p;
}
