题目链接：https://leetcode.com/problems/find-the-closest-palindrome/description/
也是一个神仙题。这个题目就是给定我们一个string（一个数字），然后要我们去找到离他最近的那个回文数。这个"最近"的意思就是绝对值相差的最小。
如果有相等的情况，就返回数值小的那个
The input n is a positive integer represented by string, whose length will not exceed 18.
如果我们要找最近的那个数，那也就是说我们要尽可能的使得差值最小，如果差值最小又是回文，我们应该尽可能的保留高位，然后改变低位
比如1234 我们可以找到4334 也可以找到1221 很明显，1221 是最优的解。那么现在这个题就可以变成我们要根据左边半段去改变右边半段的数字。
这里有需要分为几种情况讨论：
1. 原来这个数本身就是回文数，那么我们需要对这个数中间的那一位进行-1或者+1的操作。比如"181" => "171" or "191" 当然：例如"101"这种会在后面讨论
2. 如果原来的数不是回文，那么我们就需要根据前面半段的数字来修改后半段的数字，"1234" => "1221"，但"123" => "121"
但上面的方法很繁琐，如果单纯的按照上面的方法来做，code会很不clean，tricky的地方就是: 每次我们都取 (len+1)/2来操作，比如"1234"取出"12"，"100"也取出“10”
然后我们对于取出来的数进行-1, +0, +1的操作，再reverse之后拼接起来即可
另外的corner case就是对于一个4位数，他的最小的可能的回文数应该是"999"，而最大的可能的回文数是"10001"，这样我们能够处理所有的情况了。

代码如下：

class Solution {
public:
    string nearestPalindromic(string n) {
        long num = stol(n);
        int size_ = n.size();
        long lower = pow(10, size_ - 1) - 1;
        long upper = pow(10, size_) + 1; 
        unordered_set<long> st;
        st.insert(lower);
        st.insert(upper);
        //-1 0 1 对前半部分进行这样的操作
        for(int k = -1; k <= 1; ++k){
            string t = n.substr(0, (size_ + 1)/2);
            long val = stol(t) + k;
            t = to_string(val);
            t = t + string(t.rbegin() + size_%2, t.rend());
            st.insert(stol(t));
        }
        st.erase(num);
        long diff = LONG_MAX;
        long res = 0;
        for(auto val : st){
            if(abs(val - num) < diff){
                diff = abs(val - num);
                res = val;
            }else if(abs(val - num) == diff){
                res = min(val, res);
            }
        }
        return to_string(res);
    }
};
