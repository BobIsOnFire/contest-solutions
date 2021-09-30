class Solution {
public:
    int longestValidParentheses(string s) {
        int level = 0;
        int max_valid = 0;
        
        int opens[30002];
        opens[0] = -1, opens[1] = -1;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                level++;
                if (opens[level] <= opens[level - 1]) opens[level] = i;
                opens[level + 1] = -1;
                continue;
            }
            
            // validity breaks
            if (level == 0) {
                opens[0] = i;
                continue;
            }
            
            max_valid = max(max_valid, i - opens[level] + 1);
            level--;
        }
        
        return max_valid;
    }
};
