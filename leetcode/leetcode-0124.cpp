/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct stats {
    int max_overall;
    int max_root;
};

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        return process(root).max_overall;
    }
private:
    int max_of_four(int v1, int v2, int v3, int v4) {
        return max(max(v1, v2), max(v3, v4));
    }
    
    stats process(TreeNode* node) {
        if (node == nullptr) return {-1001, -1001};
        
        stats left = process(node->left);
        stats right = process(node->right);
        
        int max_root = max(max(left.max_root, right.max_root), 0) + node->val;
        
        int max_overall = max_of_four(
            left.max_overall,
            right.max_overall,
            left.max_root + right.max_root + node->val,
            max_root
        );
        
        return {max_overall, max_root};
    }
};
