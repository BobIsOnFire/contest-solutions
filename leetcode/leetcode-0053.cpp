class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max_sum = -100000;
        int cur_sum = -100000;
        
        for (int num : nums) {
            cur_sum = max(cur_sum + num, num);
            max_sum = max(max_sum, cur_sum);
        }
        
        return max_sum;
    }
};
