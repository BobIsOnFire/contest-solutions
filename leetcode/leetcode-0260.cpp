class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int xor1 = 0;
        for (auto num : nums) xor1 ^= num;
        int lowest_bit = 1;
        while (!(xor1 & lowest_bit)) lowest_bit <<= 1;
        
        int xor2 = 0;
        for (auto num : nums) if (num & lowest_bit) xor2 ^= num;
        
        return {xor2, xor1 ^ xor2};
    }
};
