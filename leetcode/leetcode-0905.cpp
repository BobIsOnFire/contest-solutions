class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        vector<int> B(A.size());
        int pointer = 0;
        for (int i = 0; i < A.size(); i++){
            if (A[i]%2 == 0) {
                B[pointer] = A[i];
                pointer++;
            }
        }
        for (int i = 0; i < A.size(); i++){
            if (A[i]%2 != 0) {
                B[pointer] = A[i];
                pointer++;
            }
        }
        return B;
    }
};
