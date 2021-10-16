class Solution {
public:
    bool buddyStrings(string A, string B) {
        if (A.length() != B.length()){
            return false;
        }
        if (A == B){
            int letterCount[5] = {0};
            for (int i = 0; i < A.length(); i++){
                letterCount[A.at(i) - 'a']++;
            }
            for (int c: letterCount){
                if (c > 1){
                    return true;
                }
            }
            return false;
        }else{
            int difOne = -1;
            int difTwo = -1;
            for (int i = 0; i < A.length(); i++){
                if (A[i] != B[i]){
                    if  (difOne == -1){
                     difOne = i;
                    } else if (difTwo == -1){
                        difTwo = i;
                    }else {
                        return false;
                    }
                }
            }
            return (difTwo != -1 && A [difOne] == B[difTwo] && A[difTwo] == B[difOne]);
        }
    } 
};
