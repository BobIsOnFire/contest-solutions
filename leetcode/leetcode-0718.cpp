class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int dp[1001][1001];
        int M = nums1.size();
        int N = nums2.size();
        
        int max = 0;
        
        for (int i = 0; i <= M; i++) dp[i][N] = 0;
        for (int j = 0; j <= N; j++) dp[M][j] = 0;

        for (int i = M - 1; i >= 0; i--) {
            for (int j = N - 1; j >= 0; j--) {
                if (nums1[i] == nums2[j]) dp[i][j] = dp[i+1][j+1] + 1;
                else dp[i][j] = 0;
                
                if (dp[i][j] > max) max = dp[i][j]; 
            }
        }
        
        return max;
    }
};
