struct Results {
    constexpr Results(): table() {
        table[0] = 1;
        int i = 0, j = 0, k = 0;
        int idx = 0;
        while (idx < 1689)
        {
            table[++idx] = min(table[i] * 2, min(table[j] * 3, table[k] * 5));
            if (table[idx] == table[i] * 2) ++i;
            if (table[idx] == table[j] * 3) ++j;
            if (table[idx] == table[k] * 5) ++k;
        }
    }
    
    int table[1690];
};

class Solution {
public:
    int nthUglyNumber(int n) {
        constexpr auto results = Results();
        return results.table[n-1];
    }
};
