struct level {
    int left;
    int right;
    int count;
};

struct level m_default = (struct level) {30001, -1, 0};

int trap(int* height, int heightSize){
    struct level levels[100001];
    for (int i = 0; i < 100001; i++) levels[i] = m_default;
    
    int max_height = 0;
    for (int i = 0; i < heightSize; i++) {
        int h = height[i];
        if (h > max_height) max_height = h;
        
        struct level *l = &levels[h];
        
        l->count++;
        if (i < l->left) l->left = i;
        if (i > l->right) l->right = i;
    }
        
    struct level current = m_default;
    long sum = 0;
    
    for (int i = max_height; i > 0; i--) {
        struct level *l = &levels[i];
        
        current.count += l->count;
        if (current.left > l->left) current.left = l->left;
        if (current.right < l->right) current.right = l->right;
        
        sum += current.right - current.left - current.count + 1;
    }
    
    return sum;
}
