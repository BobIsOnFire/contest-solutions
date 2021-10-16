class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        unordered_map<int, vector<pair<int,int>>> crazy_map;
        
        int n = nums.size();
        for (int i = 0; i < n-1; i++) {
            if (nums[i] == nums[i+1]) {
                if (nums[i] <= 0) crazy_map[2*nums[i]].push_back({i,i+1});
                while (i < n-1 && nums[i] == nums[i+1]) i++;
            }
            for (int j = i+1; j < n; j++) {
                if (nums[i] + nums[j] >= 0) continue;
                crazy_map[nums[i] + nums[j]].push_back({i,j});
                while (j < n-1 && nums[j] == nums[j+1]) j++;
            }
        }
                
        vector<vector<int>> result;
        for (int k = 0; k < n; k++) {
            if (nums[k] < 0) continue;
            if (k < n-1 && nums[k] == nums[k+1]) continue;
            vector<pair<int,int>> &value = crazy_map[-nums[k]];
            for (auto p : value) {
                if (k <= p.second) continue;
                result.push_back({nums[p.first], nums[p.second], nums[k]});
            }
        }
        
        return result;
    }
};
