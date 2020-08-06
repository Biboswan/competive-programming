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
class Solution {
public:
    TreeNode* last;
    bool inorder(TreeNode* node) {
        if (node==nullptr) {
            return true;
        }
        bool r;
        r = inorder(node->left);
        if (r==false) {
            return false;
        }
        if (last!=nullptr && last->val>=node->val) {
            return false;
        }
        last = node;
        r=inorder(node->right);
        return r;
    }

    bool isValidBST(TreeNode* root) {
        return inorder(root);
    }
};
