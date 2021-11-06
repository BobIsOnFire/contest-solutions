class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int k = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[k] > nums[i]) break;
            if (nums[k] == nums[i]) continue;
            swap(nums[++k], nums[i]);
        }
        
        return k+1;
    }
};
