题目链接：https://leetcode.com/problems/binary-tree-cameras/description/
二叉树照相机问题，当时比赛的时候，博主想用greedy的方法来做，果不其然的过不了test case：[0,0,null,null,0,0,null,null,0,0]
看来只能用DP这也是DP强大的地方。
这道题目说给定一棵二叉树，这个二叉树里面放置cameras，这个cameras能够拍摄到他的父节点，node自身，以及左右直接子树。
问至少需要多少个节点，才能完完全全的覆盖整棵树。一般这种求最少最多的题，大概率会是Greedy/DP算法。
这个题的dp思路就比如当前我站在node，这个node要么被覆盖，要么没有被覆盖，如果被覆盖有两种情况，一是他自身放了一个cameras，或者没有放cameras但他的直接子树
能够覆盖这个点。因此我们dp是自下而上的，每次返回一个vector。
        //分三种状态来看，自下而上的dfs，
        //1. 如果它的（直接和间接）子节点们都已经被cover了，但它自己没有被cover，也就是告诉它的父节点 必须要place一个。
        //2. 如果它以及它的（直接和间接）子节点们都已经被cover了，但是Camera不在他这里，也就是说他是被某个子节点的Camera而cover的，那么他的父节点可以选择不place Camera，也可以选择place Camera。
        //3. 如果它以及它的（直接和间接）子节点们都已经被cover了，而且Camera在他这里，也就是说他是被自己的的Camera而cover的，那么他的父节点尽量不要选择place Camera。
        
        
class Solution {
public:
    int minCameraCover(TreeNode* root) {
        auto vec = dfs(root);
        return min(vec[1], vec[2]);
    }
    
    vector<int> dfs(TreeNode* root){
        if(root == nullptr) return {0, 0, 10000};
        //这个地方是root的时候，首先，如果我们想要子树都被cover，root不cover，当然为0. 想要子树cover，而且root也co//r，那也为0. 
        //还要在这里放一个Camera，设置为无穷大。如果不设置为无穷大，比如我们只有一个node，那么左边进去返回[0,0,0] 右边进去返回[0,0,0] 那么对于这个root，三个值就是[0,0,1], 最后就会返回为0、 
        //如果设置成了无穷大，结果就是左边[0,0, INT_MAX], 右边[0,0,INT_MAX] 最后root 返回 [0, 10000, 1]. 结果才正确
        auto l = dfs(root->left);
        auto r = dfs(root->right);
        int minl = min((int)l[1], (int)l[2]);
        int minr = min((int)r[1], (int)r[2]);
        //status0: 如果你想左右两边都被cover，那就直接在l的1。2状态，和r的1.2状态分别挑选最小的，然后相加即可
        int status0 = minl + minr;
        //status1: 如果你想当前root也被cover，那么左右两边至少要有一个node 当然两边同时都有相机会使很浪费的，所以就是min(l[2] + minr, minl + r[2]）
        int status1 = min(l[2] + minr, min(minl + r[2], l[2] + r[2]));
        //status2：你如果想当前的root也被cover，而且你在root放了相机，那就直接左边三个case 取min，右边是三个case取min即可
        int status2 = 1 + min(l[0], minl) + min(r[0], minr);
        return {status0, status1, status2};
    }
};


附上一些test case：
/*
[0,0,null,0,0]
[0,0,null,0,null,0,null,null,0]
[0,0,null,0,0]
[0,0,null,0,null,0,null,null,0,null,0,0,null,0,null,0,null,null,0,0,0,null,0,null,0,null,null,0,0,0,null,0,null,0,null,null,0,null,0,0,null,0,null,0,null,null,0,0,0,null,0,null,0,null,null,0,null,null,0,0,null,0,null,0,null,null,0]
[0]
[0,0,null,null,0,0,null,null,0,0]
[0,0,null,null,0,0,null,null,0,0,0,0,null,null,0,0,null,null,0,0,0,0,null,null,0,0,null,null,0,0,0,0,null,null,0,0,null,null,0,0,0,0,null,null,0,0,null,null,0,0]
*/
