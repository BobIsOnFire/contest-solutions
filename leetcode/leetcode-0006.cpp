class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        int n = s.length();
        string res (n, ' ');
        int idx = 0;
        int step = (numRows - 1) * 2;
        
        for (int i = 0; i < numRows; i++) {
            for (int j = i; j < n; j += step) {
                res[idx++] = s[j];
                int aux = j + (numRows-i-1)*2;
                if (i != 0 && i != numRows-1 && aux < n) res[idx++] = s[aux];
            } 
        }
        return res;
    }
};
