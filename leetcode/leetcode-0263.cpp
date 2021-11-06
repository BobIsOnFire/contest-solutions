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
    bool isUgly(int n) {
        constexpr auto res = Results();
        return search(res.table, n, 0, 1689);
    }
    
    bool search(int const * table, int n, int i, int j) {
        if (j < i) return false;
        int idx = (i + j) / 2;
        if (table[idx] == n) return true;
        if (table[idx] < n) return search(table, n, idx + 1, j);
        else return search(table, n, i, idx - 1);
    }
};
