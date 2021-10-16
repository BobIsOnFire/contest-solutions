class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        result.push_back(string(2*n, 0));
        
        dfs(result, 0, 0, n, 0);
        return result;
    }
private:
    void dfs(vector<string> &result, int idx, int offset, int n, int depth) {
        while (offset < 2*n) {
            if (depth == n || offset + depth == 2*n) {
                result[idx][offset++] = ')';
                depth--;
                continue;
            }
            
            if (depth == 0) {
                result[idx][offset++] = '(';
                depth++;
                continue;
            }
            
            int s = result.size();
            result.push_back(result[idx]);
            result[s][offset] = ')';
            dfs(result, s, offset+1, n, depth-1);
            
            result[idx][offset++] = '(';
            depth++;
        }
    }
};
