class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        return strs[0].substr(0, find_index(strs));
    }
private:
    int find_index(vector<string>& strs) {
        int idx = 0;
        while (true) {
            char c = strs[0][idx];
            for (auto s : strs) {
                cout << s[idx];
                if (idx == s.length()) return idx;
                if (s[idx] != c) return idx;
            }
            cout << "\n";
            idx++;
        }
    }
};
