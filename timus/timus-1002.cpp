#include <bits/stdc++.h>

struct trie_node {
    trie_node * next[26] = {0};
    std::string * word_end = NULL;
} nodes[300000];
int last_node = 0;

struct traverse {
    std::string * words[100];
    trie_node * current = NULL;
    int count = 0;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    while (true) {
        std::string number;
        std::cin >> number;

        if ("-1" == number) break;

        // TODO: initialize trie

        int size;
        std::cin >> size;
        std::vector<std::string> vocab(size, "");

        for (int i = 0; i < size; i++) {
            std::cin >> vocab[i];
            // TODO: insert nodes into trie
        }

        std::vector<traverse> mnemonics;
        mnemonics.reserve(number.length());

        mnemonics.push_back({
            .current = &nodes[0]
        });

        for (const char &ch : number) {
            int n = mnemonics.size();
            for (int i = 0; i < n; i++) {
                traverse &t = mnemonics[i];
                if (t.current == NULL) continue;

                t.current = t.current->next[ch - 'a'];
                if (t.current == NULL) continue;

                if (t.current->word_end != NULL) {
                    t.words[t.count++] = t.current->word_end;
                    // TODO: add new node that copies t, but t.current is &nodes[0] (?)
                }
            }
        }

        int min_idx = -1;
        int min_count = 1000;
        for (int i = 0; i < mnemonics.size(); i++) {
            const traverse &t = mnemonics[i];
            // Check that traversal actually ended when number ended
            if (t.current != &nodes[0]) continue;
            if (t.count < min_count) {
                min_count = t.count;
                min_idx = i;
            }
        }

        if (min_idx == -1) std::cout << "No solution.\n";
        else {
            for (std::string *w : mnemonics[min_idx].words) {
                std::cout << *w << " ";
            }
            std::cout << "\n";
        }
    }
}