int merged[2000];

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int k = 0;
    for (int i = 0, j = 0; i < nums1Size || j < nums2Size;) {
        if (i >= nums1Size) merged[k++] = nums2[j++];
        else if (j >= nums2Size) merged[k++] = nums1[i++];
        else merged[k++] = (nums1[i] < nums2[j]) ? nums1[i++] : nums2[j++];
    }
    
    if (k & 1) return merged[k/2];
    return ( merged[k/2 - 1] + merged[k/2] ) / 2.0;
}
