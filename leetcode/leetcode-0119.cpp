class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> row = vector<int>(rowIndex + 1);
        
        row[0] = 1;
        row[rowIndex] = 1;
        
        for (int i = 1; i <= rowIndex / 2; i++) {
            long res = long(row[i - 1]) * (rowIndex - i + 1) / i;
            row[i] = res;
            row[rowIndex - i] = res;
        }
        
        return row;
    }
};
