class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i <= 31; i++) {
            int check = 1 << i;
            int count = 0;
            for (auto num : nums) {
                if (num & check) count++;
            }
            if (count % 3) res |= check;
        }
        return res;
    }
};
