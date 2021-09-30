bool isMatch(char * s, char * p){
    bool states[21][32];
    int N = 0;
    for (; p[N]; N++);

    states[0][0] = true;
    for (int j = 1; j < N + 2; j++)
        states[0][j] = p[j-1] == '*' && states[0][j-2];
        
    int i = 0;
    for(; s[i]; i++) {
        for (int j = 0; j < N + 2; j++) {
            states[i+1][j] = false;
        }
        
        for (int j = 0; j < N; j++) {
            bool state = states[i][j];
            
            bool simple_match = p[j] == '.' || p[j] == s[i];
            bool wildcard_match = p[j] == '*' && (p[j-1] == '.' || p[j-1] == s[i]);
                        
            states[i+1][j] |= state && wildcard_match;
            states[i+1][j+1] |= state && (simple_match || wildcard_match);
            states[i+1][j+2] |= state && simple_match && p[j+1] == '*';
            
            states[i+1][j+2] |= p[j+1] == '*' && states[i+1][j];
        }
    }
    
    return states[i][N];
}
