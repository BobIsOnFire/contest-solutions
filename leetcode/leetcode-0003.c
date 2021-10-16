int lengthOfLongestSubstring(char * s){
    int ch[128]; // last index of each ASCII symbol
    for (int i = 0; i < 128; i++) ch[i] = -1;
    
    int beg = -1; // beginning of current unrepeating sequence
    int i = 0;
    int max = 0;
    for (; *s > 0; s++) {
        int c = ch[*s];
        if (beg <= c) beg = c + 1;
        ch[*s] = i;
       
        if (i - beg + 1 > max) max = i - beg + 1;
        i++;
    }
        
    return max;
}
