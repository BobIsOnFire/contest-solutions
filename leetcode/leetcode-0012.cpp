class Solution {
public:
    string intToRoman(int num) {
        return mapper[3][num / 1000] + 
               mapper[2][num / 100 % 10] +
               mapper[1][num / 10 % 10] +
               mapper[0][num % 10];
    }
    
private:
    vector<string> mapper[4] = {
        {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
        {"", "M", "MM", "MMM"},
    };
};
