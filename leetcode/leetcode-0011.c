struct pair {
    int leftest;
    int rightest;
};

int maxArea(int* height, int heightSize){
    struct pair pairs[10001];
    for (int i = 0; i < 10001; i++) pairs[i] = (struct pair) {10001, -1};
    
    int max_height = 0;
    
    for (int i = 0; i < heightSize; i++) {
        int h = height[i];
        if (h > max_height) max_height = h;
        
        struct pair *p = &pairs[h];
        if (i < p->leftest) p->leftest = i;
        if (i > p->rightest) p->rightest = i;
    }
        
    struct pair current = (struct pair) {10001, -1};
    int max = 0;
    
    for (int i = max_height; i > 0; i--) {
        struct pair p = pairs[i];
        if (current.leftest > p.leftest) current.leftest = p.leftest;
        if (current.rightest < p.rightest) current.rightest = p.rightest;
        
        int sq = (current.rightest - current.leftest) * i;
        if (sq > max) max = sq;
    }
    
    return max;
}
