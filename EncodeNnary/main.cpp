/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * }; * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

//https://sean8purdue.gitbooks.io/algs/n-ary-tree/encode-n-ary-tree-to-binary-tree.html

class Solution {
public:
    /**
     * @param root: binary tree
     * @return: N-ary tree
     */
    UndirectedGraphNode* decode(TreeNode * root) {
        // write your code here
        if (root == nullptr) {
            return nullptr;
        }
        
        UndirectedGraphNode* n = new UndirectedGraphNode(root->val);
        TreeNode* t=root->right;
        while(t) {
            n->neighbors.push_back(decode(t));
            t=t->left;
        }
        
        return n;
    }

    /**
     * @param root: N-ary tree
     * @return: binary tree
     */
    TreeNode * encode(UndirectedGraphNode* root) {
        // write your code here
        if (root == nullptr) {
            return nullptr;
        }
        
        TreeNode * n = new TreeNode(root->label);
        int childs = root->neighbors.size();
        if (childs > 0) {
            n->right = encode(root->neighbors[0]);
            TreeNode* t = nullptr;
            int i=1;
            t=n->right;
            while(i<childs) {
                t->left = encode(root->neighbors[i++]);
                t=t->left;
            }
        }
    
        return n;
    }
};
