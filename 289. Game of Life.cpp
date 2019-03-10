题目链接：https://leetcode.com/problems/game-of-life/description/
生存游戏
题目比较绕，给定一个n*n的矩阵，里面的value是0或者1，0代表死亡，1代表存活。每个cell有8个方向：
Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
对于活细胞而言：
如果周围少于2个活细胞=>死亡
周围有2个或者3个活细胞=>存活
周围超过3个活细胞=>死亡

一个死细胞如果周围有3个活细胞=>诈尸复活
但问题是所有的更新都是同时的，而且题目要求了O(1)的space 也就是in-place replacement
方法：因为我们的状态最多也就是0，1，所以用一个二位数去临时储存信息：
next status * 10 + current status。然后count的时候就用current status，最后扫一遍更新的时候，用next status即可。

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        vector<vector<int>> dir = {{0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1}};
        if(board.empty()) return;
        int m = board.size();
        int n = board[0].size();
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                int count = 0;
                //eight neighbors .........
                for(auto d : dir){
                    int ii = i + d[0];
                    int jj = j + d[1];
                    if(ii >= m || ii < 0 || jj >= n || jj < 0) continue;
                    //这里你一定要用next status * 10 因为如果是cur*10 那么有可能cur = 0，然后next = 1.这样就出现计算错误！
                    count += (board[ii][jj] >= 10 ? board[ii][jj]%10 : board[ii][jj]);
                }
                int next_status = 0;
                if(board[i][j] == 1){
                    if(count < 2){
                        next_status = 0;
                    }else if(count <= 3){
                        next_status = 1;
                    }else{
                        next_status = 0;
                    }
                }else{
                    next_status = count == 3;
                }
                board[i][j] = board[i][j]+ next_status*10;
            }
        }
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                board[i][j] = board[i][j]/10;
            }
        }
        return;
    }
};
