#include <bits/stdc++.h>

bool comparator(const std::pair<char, int> &p1, const std::pair<char, int> &p2) {
    return p1.second > p2.second;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int chars[26] = {0};
    int weights[26] = {0};

    std::string word;
    std::cin >> word;

    for (char ch : word) chars[ch - 'a']++;
    for (int i = 0; i < 26; i++) std::cin >> weights[i];

    std::vector<std::pair<char, int>> sorted_weights; 

    for (int i = 0; i < 26; i++) {
        if (chars[i] >= 2) {
            sorted_weights.emplace_back('a' + i, weights[i]);
            chars[i] -= 2;
        }
    }

    std::sort(sorted_weights.begin(), sorted_weights.end(), comparator);

    for (int i = 0; i < sorted_weights.size(); i++) {
        word[i] = sorted_weights[i].first;
        word[word.length() - i - 1] = sorted_weights[i].first;
    }

    int idx = sorted_weights.size();
    for (int i = 0; i < 26; i++) {
        while (chars[i]-- > 0) word[idx++] = i + 'a';
    }

    std::cout << word;
}