题目链接: https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/description/

题目说的很绕. 就是给定一个数组, 里面有>0的数字, 然后这些数字作为一棵树的leaf节点(leaf是说没有子节点的所有nodes).
然后给定的这个数组的顺序,就是这些leaf nodes在中序遍历意义下的顺序. 其实就是告诉你 这些leaf nodes从左到右依次排开.
每个node要么没有子节点(leaf node), 要么就有2个节点.
The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree respectively.
每个非叶子节点的值,是等于他的左子树里最小的叶节点的值 乘以 他的右子树里最小的叶节点的值 注意 这里是最小的叶节点value
整个树的sum是等于所有非叶子节点的值的和
求这个最小的值
绕来绕去的...其实可以用dfs + memorization解

class Solution {
public:
    //dfs + memo
    int res = 0;
    vector<vector<vector<int>>> memo;
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        memo.resize(n, vector<vector<int>>(n));
        auto v = dfs(arr, 0, n-1);
        return v[1];
    }
    
    vector<int> dfs(vector<int>& arr, int i, int j){
        if(i > j) return {0,0};
        if(i == j) return {arr[i], 0};
        if(!memo[i][j].empty()) return memo[i][j];
        int left_max = 0;
        int right_max = 0;
        int sum = 100000;
        int product = 100000;
        for(int k = i; k + 1 <= j; ++k){
            auto l = dfs(arr, i, k);
            auto r = dfs(arr, k+1, j);
            
            //获取最大的左右子树里的leaf节点
            left_max = max(l[0], left_max);
            right_max = max(r[0], right_max);
            
            //为了保证整体的和最小, 这里我们取最小的root value = left_max*right_max
            if(sum + product > l[1] + r[1] + left_max*right_max){
                product = left_max*right_max;
                sum = l[1] + r[1];
            }
        }
        memo[i][j] = {max(left_max, right_max), sum + product};
        return memo[i][j];
    }
};
