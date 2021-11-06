class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int pivot = find_pivot(nums, 0, n-1);
        return bisect(nums, pivot, (pivot + n-1) % n, target);
    }
private:
    int find_pivot(vector<int>& nums, int start, int end) {
        if (nums[start] <= nums[end]) return start;
        while (true) {
            if (end - start <= 1) return end;
            int mid = (start + end) / 2;
            if (nums[mid] < nums[start]) end = mid;
            else start = mid;
        }
    }
    
    int bisect(vector<int> &nums, int start, int end, int target) {
        int n = nums.size();
        while (true) {
            if (nums[end] < target || nums[start] > target) return -1;
            if (nums[start] == target) return start;
            if (nums[end] == target) return end;
        
            int mid;
            if (end < start) mid = ((end + start + n) / 2) % n;
            else mid = (end + start) / 2;
                
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) start = (mid+1 + n) % n;
            else end = (mid-1 + n) % n;
        }
    }
};

