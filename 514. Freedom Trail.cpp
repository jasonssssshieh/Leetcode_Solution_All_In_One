题目链接：https://leetcode.com/problems/freedom-trail/description/

【自由之路】对博主有深远影响的一道题。
算法：DFS+Memorization, Dynamic Programming
这个题给定我们两个字符串string： string ring, string key。ring相当于一个轮盘，我们要转动这个轮盘，用最短的步数拼出key string。
非常明显的dp题。这里ring由于看做一个轮盘，所以相当于首尾相连了。另外，题目中给出了：
Initially, the first character of the ring is aligned at 12:00 direction. 
You need to spell all the characters in the string key one by one by rotating the ring clockwise or anticlockwise to make 
each character of the string key aligned at 12:00 direction and then by pressing the center button.
初始指向12点钟方向，同时我们每次移动一次算一步，而且press the button也算一次。因此总步数应该是转动ring的步数+key string的长度。
另外题目里说明了一定能匹配成功，也就是存在解，否则还需要判断key里面的字符是否都在ring里面出现。
首先dfs+ Memorization的方法来做，更容易理解：
采用dfs的方法：当前我的i指针是在ring的index = i位置，我需要从这里开始去匹配key string的第j个char，我的memo[i][j] 就代表了当前我的i指针是在ring的index = i位置，我需要从这里开始去匹配key string的第j个char，所需要的最小的步数。初始设置为INT_MAX/2。
最后返回dp[0][0]即可。

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        //自由之路
        if(ring.empty() || key.empty()) return 0;
        //DFS+memo
        int m = ring.size();
        int n = key.size();
        vector<vector<int>> memo(m, vector<int>(n, 0));
        vector<vector<int>> count(26);
        for(int i = 0; i < ring.size(); ++i){
            count[ring[i] - 'a'].push_back(i);
        }
        return dfs(ring, key, count, 0, 0, memo) + key.size();
    }
    
    int dfs(string& ring, string& key, vector<vector<int>>& count, int i, int j, vector<vector<int>>& memo){
        if(j == key.size()) return 0;
        if(memo[i][j]) return memo[i][j];
        int res = INT_MAX/2;
        for(auto idx : count[key[j] - 'a']){
            int dist = abs(i - idx);
            dist = min(dist, (int)ring.size() - dist);
            res = min(res, dist + dfs(ring, key, count, idx, j+1, memo));
        }
        memo[i][j] = res;
        return res;
    }
};

同理，上面的dfs也可以换成dp来做。dp[i][j]也依然表示：当前我的i指针是在ring的index = i位置，我需要从这里开始去匹配key string的第j个char，[i][j] 就代表了当前的i指针是在ring的index = i位置，我需要从这里开始去匹配key string的第j个char，所需要的最小的步数。
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        if(ring.empty() || key.empty()) return 0;
        int m = ring.size();
        int n = key.size();
        vector<vector<int>> count(26);
        for(int i = 0; i < ring.size(); ++i){
            count[ring[i] - 'a'].push_back(i);
        }
        vector<vector<int>> dp(n+1, vector<int>(m, 0));
        for(int i = n-1; i >= 0; --i){
            for(int j = 0; j < m; ++j){
                dp[i][j] = INT_MAX/2;
                for(auto idx : count[key[i] - 'a']){
                    int dist = abs(j - idx);
                    dist = min(dist, m - dist);
                    dp[i][j] = min(dp[i][j], dist + dp[i+1][idx]);
                }
                dp[i][j]++;//自己press count+1
            }
        }
        return dp[0][0];
    }
};
