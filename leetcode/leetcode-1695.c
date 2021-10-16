int ch[10001]; // last index of each number
int sum[100001]; // sum of elements from start to #i-1

int maximumUniqueSubarray(int* nums, int numsSize){
    for (int i = 0; i < 10001; i++) ch[i] = -1;
    
    sum[0] = 0;

    int beg = -1; // beginning of current unrepeating sequence
    int max = 0;
    
    for (int i = 0; i < numsSize; i++) {
        sum[i+1] = sum[i] + nums[i];
        int c = ch[nums[i]];
        if (beg <= c) beg = c + 1;
        ch[nums[i]] = i;

        int cur = sum[i+1] - sum[beg];
        if (cur > max) max = cur;
    }

    return max;
}

