bool isMatch(char * s, char * p){
    bool states_from[2002], states_to[2002];
    int N = 0;
    for (; p[N]; N++);

    states_to[0] = true;
    for (int i = 1; i < N + 2; i++)
        states_to[i] = p[i-1] == '*' && states_to[i-1];
    
    for(; *s; s++) {
        for (int i = 0; i < N + 2; i++) {
            states_from[i] = states_to[i];
            states_to[i] = false;
        }
        
        for (int i = 0; i < N; i++) {
            bool state = states_from[i];
            
            bool simple_match = p[i] == '?' || p[i] == *s;
            bool wildcard_match = p[i] == '*';
            
            states_to[i] |= state && wildcard_match;
            states_to[i+1] |= state && (simple_match || wildcard_match);
            
            states_to[i+1] |= p[i] == '*' && states_to[i];
        }
    }
    
    return states_to[N];
}
