题目链接：https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/
移石子。G家被问烂了的题，好像被ban了。

给定一个二维平面，有一些石子（点）坐标。我们现在开始移去石子，移动的规则就是必须在这个石子的同一列或者同一行还有其他的石子，才能被移动。否则不能移动
问我们最多能够移动多少石子（留在平面上的最少的石子的数目）

很明显的Union Find 并查集查找（https://github.com/jasonssssshieh/Union_Find）：
同一行或者同一列的石子union起来，最后的并查集的个数就是剩在盘面的石子，总数-number of unions 
就是我们需要求的最多移动的个数。

代码：

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        //就是石头的总数 减去联通UNION 区域的个数 就是最多能拿的次数
        if(stones.empty()) return 0;
        int n = stones.size();
        //stones[i][j] 最大不超过 10000
        vector<int> parent(20000, -1);
        int unionRegion = 0;
        for(int i = 0; i < stones.size(); ++i){
            int x = stones[i][0];
            if(parent[x] == -1){
                parent[x] = x;
                unionRegion++;
            }
            int y = stones[i][1];
            if(parent[y + 10000] == -1){
                parent[y + 10000] = y + 10000;
                unionRegion++;
            }
            UNION(x, y+10000, parent, unionRegion);
        }
        return n - unionRegion;
    }
    
    int find_parent(int x, vector<int>& parent){
        int t = x;
        while( t != parent[t]) t = parent[t];
        parent[x] = t;
        return t;
    }
    
    void UNION(int x, int y, vector<int>& parent, int& unionRegion){
        int p1 = find_parent(x, parent);
        int p2 = find_parent(y, parent);
        if(p1 != p2){
            unionRegion--;
            if(p1 < p2){
                parent[p2] = p1;
            }else{
                parent[p1] = p2;
            }
        }
        return;
    }
};
