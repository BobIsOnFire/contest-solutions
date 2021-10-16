#define MAX (int)(0x7FFFFFFF)
#define MIN (int)(0x80000000)

class Solution {
public:
    int myAtoi(string s) {
        int idx = 0;
        long num = 0;
        int mul = 1;
        
        while(s[idx] == ' ') idx++;
        
        if (s[idx] == '+') idx++;
        else if (s[idx] == '-') {
            mul = -1;
            idx++;
        }
        
        while (s[idx] && s[idx] >= '0' && s[idx] <= '9') {
            num = num * 10 + (s[idx++] - '0');
            if (mul == 1 && num > MAX) return MAX;
            if (mul == -1 && -num < MIN) return MIN;
        }
        
        return num * mul;
    }
};
