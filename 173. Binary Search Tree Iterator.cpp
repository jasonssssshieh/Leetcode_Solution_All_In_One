題目連接:https://leetcode.com/problems/binary-search-tree-iterator/description/

設計一個二叉搜索樹的中序遍歷iterator
next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
所以不能把BST先轉化成sorted array來做  沒什麼好說的 stack + 中序遍歷即可

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    //next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree. 也就是說不能先把所有的數字都存下來 然後一個個pop
    stack<TreeNode*> sk;
    TreeNode* cur;
    BSTIterator(TreeNode* root) {
        cur = root;
    }
    
    /** @return the next smallest number */
    int next() {
        hasNext();
        TreeNode* node = sk.top(); sk.pop();
        int res = node->val;
        if(node->right){
            cur = node->right;
        }
        return res;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        while(cur){
            sk.push(cur);
            cur = cur->left;
        }
        return !sk.empty();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
