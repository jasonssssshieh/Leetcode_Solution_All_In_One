题目链接：https://leetcode.com/problems/scramble-string/description/
这个题博主首先一看，就感觉很像similar binary tree那个题，只是这个题换汤不换药的改成了string形式。
这个题就是说给两个字符串s1和s2，规则是：每个字符串可以被分割成两个非空的substring，然后每个substring又可以分割成2个非空的sub-substring 一直到只剩下一个字符
这就形成了一个二叉树：To scramble the string, we may choose any non-leaf node and swap its two children. 如果这样swap之后的两个树是相同的，返回true，如果不能满足，返回false

首先排除一些情况：s1.size() != s2.size(), s1 is empty, s2 is empty 或者 s1的出现的字符和s2的出现的字符不匹配（包括个数不同，以及其中一个string中出现过的char在另外一个没有出现过）
然后就是递归，考虑所有的可能分割情况：对于每一个分割长度len，
可以是: s1的开头len长度和s2的开头len长度的匹配，也可以是s1的开头len长度和s2的最后长度len比配
       还可以是s1的最后长度len和s2的最后长度为len的string匹配。只要有一种能够匹配成功，就返回true

递归求解：
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size() != s2.size() || s1.empty() || s2.empty()) return false;
        if(s1.size() == 1 && s1 == s2) return true;
        unordered_map<int, int> count;
        for(int i = 0; i < s1.size(); ++i){
            count[s1[i] - 'a']++;
            count[s2[i] - 'a']--;
        }
        for(auto p : count){
            if(p.second != 0) return false;
        }
        int n = s1.size();
        for(int len = 1; len < n; ++len){
            string t11 = s1.substr(0, len);
            string t12 = s1.substr(n - len);
            string t21 = s2.substr(0, len);
            string t22 = s2.substr(n-len);
            bool res = (isScramble(t11, t21) && isScramble(s1.substr(len), s2.substr(len))) || (isScramble(t11, t22) && isScramble(s1.substr(len), s2.substr(0, n-len))) || (isScramble(s1.substr(0, n-len), s2.substr(0, n-len)) && isScramble(t12, t22));
            if(res) return true;
        }
        return false;
    }
};

上面的代码能AC，但似乎看上去好像没有那么简洁，毕竟是一个hard的题目。博主也是一个追求从naive到最优解都要掌握的人，所以开始思考哪些地方可以改进
在上面递归的部分我们每次都取一段string进行递归，但最后面的子问题的string的匹配 很多情况下都是重复的求解的，所以博主就去尝试着用memorization来优化：

