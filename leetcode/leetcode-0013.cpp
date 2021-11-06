int mapper[26] = {
    0, 0, 100, 500, 0, 0, 0, 0, 1, 0, 0, 50, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 10, 0, 0
};

class Solution {
public:
    int romanToInt(string s) {
        int n = s.length();
        int nums[15];
        int prev = mapper[s[0] - 'A'];
        int res = 0;
        for (int i = 0; i < n; i++) {
            nums[i] = mapper[s[i] - 'A'];
            res += get(prev, nums[i]);
            prev = nums[i];
        }
        return res;
    }
private:
    int get(int prev, int curr) {
        if (prev * 10 == curr || prev * 5 == curr) return curr - prev - prev;
        return curr;
    }
};
