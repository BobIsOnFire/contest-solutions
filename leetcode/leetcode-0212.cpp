struct node {
    int next[26];
    string * word = nullptr;
} nodes[300001];

int global_idx = 0;

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        memset(nodes[0].next, 255, 26 * sizeof(int));
        
        for (int i = 0; i < words.size(); i++) {
            int idx = addWord(words[i]);
            nodes[idx].word = &words[i];
        }
        
        vector<string> result;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                searchWords(board, i, j, 0, result);
            }
        }
        return result;
    }
    
private:    
    int addWord(string& word) {
        int current = 0;
        for (int i = 0; i < word.length(); i++) {
            int idx = word[i] - 'a';
            if (nodes[current].next[idx] == -1) {
                ++global_idx;
                memset(nodes[global_idx].next, 255, 26 * sizeof(int));
                nodes[current].next[idx] = global_idx;
            }
            current = nodes[current].next[idx];
        }
        return current;
    }
    
    void searchWords(
        vector<vector<char>>& board, int i, int j, int node_idx, vector<string>& result) {
        char c = board[i][j];
        if (c == '#') return;
        
        int next = nodes[node_idx].next[c - 'a'];
        if (next == -1) return;
        
        if (nodes[next].word) {
            result.push_back(*nodes[next].word);
            nodes[next].word = nullptr;
        }
        
        board[i][j] = '#';
        
        if (i > 0)
            searchWords(board, i-1, j, next, result);
        if (j > 0)
            searchWords(board, i, j-1, next, result);
        if (i < board.size()-1)
            searchWords(board, i+1, j, next, result);
        if (j < board[0].size()-1)
            searchWords(board, i, j+1, next, result);

        board[i][j] = c;
    }
};
