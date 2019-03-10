题目链接：https://leetcode.com/problems/strange-printer/description/
奇怪的打印机
题目大意是给定了一个打印机，每次它只能够打一系列相同的char，并且打印的新的字符能够覆盖旧的字符
题目给定一个字符串，问最少打印次数能够打印出这个string

题目本身不难，博主当时做这个题目的时候主要是基于其中一个规律：
比如我现在打印了"abbbb", 假如我希望在末尾加一个'a' 那么由于a已经在前面打印过的部分出现过，所以其实可以减少一次打印
另外一个例子"abbb" + "ba"： 单独来看，这两个string print每个都至少需要打印2次，naive看起来就是4次。但是实际上b可以连着abbb之后打印，而第一次打印a的时候可以把最后一个a也打印了 总共2次
那么回归到这个题，dp[i][j] 就是这个string我打印[i,j]这一段的时候 需要的最少打印次数。
状态转移方程：
dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] - (s[k] == s[j]))


其实回头来想这个题如果是dfs，那么我就可以从开头结尾两端来考察，如果开头和结尾是一样的字符 那么我就可以只用一次就能打印了，
那么这样问题就变成了子问题递归[i+1, j-1]；如果不一样 那么我们就需要去在中间找一个最佳的切割点来打印，也就是我们dp里的第三个循环

代码如下：

class Solution {
public:
    int strangePrinter(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX/2));
        for(int i = 0; i < n; ++i) dp[i][i] = 1;
        for(int len = 2; len <= n; ++len){
            for(int i = 0; i + len - 1 < n; ++i){
                int j = i + len - 1;
                for(int k = i; k < j; ++k){
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] - (s[k] == s[j]));
                }
            }
        }
        return dp[0][n-1];
    }
};
