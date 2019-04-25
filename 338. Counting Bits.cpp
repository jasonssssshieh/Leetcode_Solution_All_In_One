题目链接: https://leetcode.com/problems/counting-bits/description/
恩 三年前刷过的题, 现在准备面试, 又翻出来了.
题目大意就是给你一个数字 num, 然后从0到num里面每一个数字的二进制里有多少个1
题目非常变态的要求时间和空间复杂度都为O(n)
O(n*sizeof(integer))的时间复杂度是不行的
面试里面看到面试官也是一路追问到最优解

个人的思路: 首先,0肯定是0, 然后对于2^n这种数字,一定都是1
然后再根据在2^(n-1)和2^(n)之间的这些数字进行变化:
0  1(2^0)  2(2^1)  3  4(2^2)  5  6  7  8(2^3)  9  10  11  12  13  14  15  16(2^4)
0  1         1     1     1               1
那其实就是nums[i] = nums[i>>1] + 奇数(+1) or 偶数(+0)

江湖一张纸, 戳破不值半文钱.....

class Solution {
public:
    vector<int> countBits(int num) {
        if(num < 0) return {};
        vector<int> res(num+1, 0);
        for(int i = 1; i <= num; ++i){
            res[i] = res[i>>1] + (i&1);
        }
        return res;
    }
};
