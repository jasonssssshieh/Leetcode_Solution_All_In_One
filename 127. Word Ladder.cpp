题目链接：https://leetcode.com/problems/word-ladder/description/
这个题本质上是在考察BFS。每次我们去改变每个在queue里的单词的每一个字符即可，因为这里题目中规定的单词长度是比较小的。

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        //bfs
        if(beginWord == endWord) return 0;
        unordered_set<string> st;
        st.insert(wordList.begin(), wordList.end());
        if(st.find(endWord) == st.end()) return 0;
        queue<string> q;
        q.push(beginWord);
        unordered_set<string> visited;
        //visited.insert(beginWord);
        //这里有个小tricky 就是我们可以直接用st作为visited，因为反正我们每次都是要从wordlist里面存在的单词，那么出现过的就erase 这样就不会重复了
        if(st.find(beginWord) != st.end()) st.erase(beginWord);
        int steps = 1;
        while(!q.empty()){
            int len = q.size();
            while(len){
                string s = q.front(); q.pop(); len--;
                visited.insert(s);
                for(int i = 0; i < s.size(); ++i){
                    char ch = s[i];
                    for(int j = 0; j < 26; ++j){
                        s[i] = 'a' + j;
                        if(s == endWord) return steps + 1;
                        if(s[i] != ch && st.find(s) != st.end()){
                        //if(st.find(s) != st.end() && visited.find(s) == visited.end()){
                            //visited.insert(s);
                            st.erase(s);
                            q.push(s);
                        }
                    }
                    s[i] = ch;
                }
            }
            steps++;
        }
        return 0;
    }
};



************************
这个题这样直接BFS可以通过，博主自己还测试了一下Bi-BFS，也是同样可以通过的，而且更快，同时从startWord以及endWord开始搜索结果。Bi-BFS是用两个hash set
每次交替使用其中的一个set里的string，如果能够match到另外一个set里的某个string，就return true

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if(beginWord == endWord) return 0;
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if(dict.count(endWord) == 0) return 0;
        dict.erase(beginWord);
        dict.erase(endWord);
        unordered_set<string> st1;
        st1.insert(beginWord);
        unordered_set<string> st2;
        st2.insert(endWord);
        int steps = 1;
        while(!st1.empty() || !st2.empty()){
            vector<string> temp;
            for(auto s : st1){
                for(int i = 0; i < s.size(); ++i){
                    char org = s[i];
                    for(int j = 0; j < 26; ++j){
                        if(org - 'a' == j) continue;
                        s[i] = char(j + 'a');
                        if(st2.count(s)) return steps + 1;
                        if(dict.count(s)){
                            temp.push_back(s);
                            dict.erase(s);
                        }
                    }
                    s[i] = org;
                }
            }
            st1 = st2;
            st2.clear();
            st2.insert(temp.begin(), temp.end());
            steps++;
        }
        return 0;//Return 0 if there is no such transformation sequence.
    }
};
