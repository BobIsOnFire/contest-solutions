class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int locs[30000], dists[30000];
        int k = 0;
        for (int i = 0; i < arr.size(); i++)
            if (arr[i]) locs[k++] = i;
        
        if (!k) return {0, 2};
        if (k % 3) return {-1,-1};

        for (int i = 1; i < k; i++)
            dists[i] = locs[i] - locs[i-1];

        int s = k/3;
        for (int i = 1; i < s; i++) {
            if (dists[i] != dists[i+s] || dists[i] != dists[i+2*s])
                return {-1,-1};
        }

        int trailing_dist = arr.size() - locs[k-1] - 1;
        if (dists[s] - 1 < trailing_dist || dists[2*s] - 1 < trailing_dist)
            return {-1,-1};
        return {locs[s-1] + trailing_dist, locs[2*s-1] + trailing_dist + 1};
    }
};
