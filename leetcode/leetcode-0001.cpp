class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m_map;
        for (int i = 0; i < nums.size(); i++) {
            int c = nums[i];
            auto it = m_map.find(target - c);
            if (it != m_map.end()) return {it->second, i};
            
            m_map.try_emplace(nums[i], i);
        }
        return {-1, -1};
    }
};
