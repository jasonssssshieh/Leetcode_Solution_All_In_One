/*

https://leetcode.com/problems/insufficient-nodes-in-root-to-leaf-paths/description/

本周周赛题. 我真是佛了这个题目, 比赛的时候debug了很久, 最后四个test case死活过不了.
这个题目其实出的本身有一些歧义..感觉最近几场比赛的题目描述都写的不好.LC需要多多把关.

废话不多说了. 这个题目是说给你一棵二叉树, 同时给你一个整数int limit. 
计算每一个从root到leaf的path sum, 题目定义leaf就是没有children的node
这样如果说对于某一个node, 如果经过他的每条path的sum都是小于limit的,那么这个node就是insufficient的, 需要被删除.
返回最后删除处理之后的树.
题目给的example都没什么坑,自然理解不了题目的本意

这个题目的终极含义是: 我们要删除的是中间的node,而不是leaf节点!!!
也就是说: 因为leaf肯定只会有且仅有一条path, 而且leaf一定是某条path的终点. 那么对于leaf而言这条path sum 小于limit 也是没关系的, 不用删除
而对于中间节点的node,他们的path sum 有多个,如果每一个path sum都是小于limit, 那么就要把这个点删掉变成nullptr

这个题目描述里也没有说清楚, 坑的地方就是这里
*/

class Solution {
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        return dfs(root, 0, limit);
    }
    
    TreeNode* dfs(TreeNode* root, int sum, int limit){
        if(root == nullptr) return nullptr;
        if(root->left == nullptr && root->right == nullptr && sum + root->val < limit){
            //也就是Leaf节点了 但我们并不删除 也就是不设置root = nullptr
            return nullptr;
        }
        
        bool isNotLeaf = (root->left != nullptr) || (root->right != nullptr);
        //这里标记一下,看看当前node是否是中间节点, 提前判断一下.
        root->left = dfs(root->left, sum + root->val, limit);
        root->right = dfs(root->right, sum + root->val, limit);
        if(!root->left && !root->right && isNotLeaf){
            //如果以前是非叶子节点,然后现在我们发现已经成为了叶子节点,说明他的每条path sum都是小于limit的, 那么就需要删除这个node
            root = nullptr;//进行删除,但这行其实可以省略.
            return nullptr;
        }
        return root;
    }
};
