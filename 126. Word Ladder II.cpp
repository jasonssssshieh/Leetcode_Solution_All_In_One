题目链接：https://leetcode.com/problems/word-ladder-ii/description/
Word Ladder的升级版，这题不仅是说判断能否转化，还需要我们来找到所有的转化路径。双重暴击！！难度暴增！！
题目还是很好的给了一些notes： 
Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
这个题分为两步：第一步BFS：找到最短路径，同时找到每个string能够从哪些string被转化而来
               第二步DFS：找到所有的最短路径.dfs构图。为了让dfs能够图，在bfs的时候就应该建立一个graph，也就是某一个string 能够由哪些string得来。
               用hash map就可以建表。最后dfs的时候记录路径，结束的时候判断下是不是endWord 是就push进入result
               
这里需要注意的点有：第一步bfs的时候不能像word ladder那样，遇到了endWord就break，我们需要用一个bool变量findEnd来判断是否我们已经找到了endword，
如果findEnd = true，那么我们在走完这一层的bfs之后，再break。
同时，我们bfs的时候可能遇到某个string能够由不同的string转化而来，比如一个例子：
bad->bed->bet
bad->tad->tat->bet
这里bet看上去好像是有两条path能够得到，然鹅我们只能选择并且储存第一条path，因为第二条不是最短的。

下面是代码：
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        if(wordList.empty() || beginWord == endWord) return {};
        //思路就是首先BFS找到最短距离 并且过程中构建一个graph。然后dfs找到所有的path
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if(dict.count(endWord) == 0) return {};
        dict.erase(beginWord);
        //dict.erase(endWord);
        unordered_map<string, unordered_set<string>> parent;//每一个string 可以由哪些string转换过来
        queue<string> q;
        q.push(beginWord);
        bool find = false;
        while(!q.empty() && !find){
            int len = q.size();
            unordered_set<string> visited;
            while(len){
                auto str = q.front(); q.pop(); len--;
                auto t = str;
                for(int i = 0; i < str.size(); ++i){
                    char org = str[i];
                    for(int k = 0; k < 26; ++k){
                        if(org - 'a' == k) continue;
                        str[i] = char(k + 'a');
                        if(str == endWord) find = true;
                        if(dict.count(str)){
                            parent[str].insert(t);
                            visited.insert(str);
                        }
                    }
                    str[i] = org;
                }
            }
            for(auto s : visited){
                q.push(s);
                dict.erase(s);
            }
        }
        vector<vector<string>> res;
        vector<string> path = {endWord};
        dfs(res, beginWord, endWord, parent, path);
        return res;
    }
    
    void dfs(vector<vector<string>>& res, string& beginWord, string& endWord, unordered_map<string, unordered_set<string>>& parent, vector<string>& path){
        if(beginWord == endWord){
            reverse(path.begin(), path.end());
            res.push_back(path);
            reverse(path.begin(), path.end());
            return;
        }
        for(auto p : parent[endWord]){
            path.push_back(p);
            dfs(res, beginWord, p, parent, path);
            path.pop_back();
        }
        return;
    }
};
