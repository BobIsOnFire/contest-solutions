class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        
        int max_len = 1;
        int max_idx = 0;
        
        for (int i = 0; i < n; i++) {
            int j = 0, k = 0;
            while (j <= i && j <= n - i - 1 && s[i-j] == s[i+j+1]) j++;
            while (k <= i && k <= n - i && s[i-k] == s[i+k]) k++;
            
            int v = max(2*j, 2*k-1);
            if (v > max_len) {
                max_len = v;
                max_idx = i - (v+1)/2 + 1;
            }
        }
        
        return s.substr(max_idx, max_len);
    }
};
