int reverse(int x) {
    int res = 0;
    while (x) {
        int tmp = (long) res * 10 + x % 10;
        if (tmp / 10 != res) return 0;
        res = tmp;
        x /= 10;
    }
        
    return res;
}
