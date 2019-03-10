题目链接：https://leetcode.com/problems/cat-and-mouse/description/

个人认为是2018-2019的leetcode冬季赛题里出的最好的一个题。博主也是在Google onsite前一天把这个题给看明白了，虽然面试也没被问到。
但这个题的思路也是非常有助于理解dynamic programming和博弈。其实思路理解之后写代码非常容易，稍微繁琐了一点。
好了不废话，进入题解。

题目大意是猫捉老鼠游戏，给定一个无向图，猫初始会在1并且先走，老鼠初始会在2后走，每轮一次走一步，猫的目标是捉住老鼠，老鼠的目标是回到index = 0这个位置。
另外题目规定了猫不能走到0这个位置。然后询问谁会赢这个比赛。这个题目还有一个奇特的地方就是有可能是平局。
网路上各种DFS解我也看不懂，还是来一发官方的BFS“染色”解。

首先，cat和mouse一定是去寻找最优解，那么也就是他们每走一步，都会完全预想到接下来的情况，借用dynamic programming的思维，如果我们知道了最后一次的状态，
那么前一步的时候猫或者老鼠一定会尽可能的往能够保证他们自己胜利的地方去走。
举个例子，现在cat在x位置，老鼠在y位置，当前回合是cat回合，也就是猫来走当前这一步，我们的状态status可以定义为status[x][y][cat]，
那么我们就去寻找，对于x位置，下一步能够走到哪些node，假设下一步的node有： a, b。
如果猫走到a点，那么下一步的状态就换成了，status[a][y][mouse]，也就是成了老鼠的回合，如果这个状态下，我们能够确认status[a][y][mouse]是老鼠获胜，那么上一次猫的回合，猫绝对不会走这一步，因此，对于status[x][y][cat] 我们可以走的node就只剩下b。
好，假设我们选择了b，，那么下一步的状态就换成了status[b][y][mouse]，也就是成了老鼠的回合，如果这个状态下，我们能够确认status[b][y][mouse]是老鼠获胜，那么猫也还是不会走这一条路，那么status[x][y][mouse]就无路可走，
也就是说这时候不管猫如何走，最后都是老鼠获胜，所以status[x][y][mouse]就被“染色”成为“老鼠获胜”。
同理，如果status[x][y][mouse]只要能有一条路使得猫获胜，那么猫一定会走这条路，此时status[x][y][mouse]就被“染色”成为“猫获胜”。
这个逻辑就：在A的回合，除非是没能找到一条A获胜的路，那么状态要么是对方获胜，要么是平局，否则，只要能有一条路保证A获胜，那么这个status就被染色成“A获胜”。
对于老鼠的回合也是同样的逻辑。

最后没有被染色的那些点，就是结果无法确认的点，也就是代表平局。这个地方博主也有点不是完全彻底的理解，
但个人认为就是一个动态博弈的过程，如果这个状态下双方都没法占优，那么就是无法确认，也就是平局。

下面是代码部分，有点长，但基本逻辑就是上面分析的：


class Solution {
public:
struct tuple{
    tuple(int c, int m, int t){
        m_pos = m;
        c_pos = c;
        turn = t;
    }
    int turn;
    int m_pos;
    int c_pos;
};
    int catMouseGame(vector<vector<int>>& graph) {
        //BFS 首先去确定那些状态完全可以确定的点 比如0，或者cat和mouse已经在同一个位置，就是从这些状态出发 我们来把所有的可能的状态去染色
        //同时这个题目还有一点就是：比如现在是老鼠的回合，那么只要能够找到一条最后是活命的路，那么老鼠就胜利。对于猫同理。如果是猫的回合，如果猫不能找到一条获得胜利的路，那么要么老鼠胜利 要么 平局. 就是从最后我们能确定的状态去反推他前一步的情况 也就是用确定的状态投对待定的状态 染色。
        那么如果当前是[cat_pos, mouse_pos]
                    1. 老鼠的回合，这个时候是老鼠赢了，那么前一步就是猫的回合，那么猫一定会避免走cat_pos这个点。
                    2. 老鼠的回合，这个时候猫赢了，那么前一步是猫的回合  那么猫一定会走到cat_pos这
                    3. 猫的回合，这个时候猫赢了，那么前一步是老鼠的回合  那么老鼠一定会避免走mouse_pos这个点
                    4. 猫的回合，这个时候是老鼠赢了，那么前一步是老鼠的回合  那么老鼠一定会走mouse_pos这个点。
        if(graph.size() < 3) return 0;
        vector<vector<int>> temp(51, vector<int>(3, 0));
        vector<vector<vector<int>>> status(n, vector<vector<int>>(n, vector<int>(3,0)));
        vector<vector<vector<int>>> outDegree(n, vector<vector<int>>(n, vector<int>(3,0)));//某一个点对于某一个人的回合 还能走的点
        int CAT = 2;
        int MOUSE = 1;
        int n = graph.size();
        vector<int> degrees(51, 0);
        queue<tuple> q;
        for(int i = 1; i < n; ++i){//猫的状态 猫不能在0的位置
            for(int j = 0; j < n; ++j){//老鼠的状态
                if(j == 0){
                    status[i][j][CAT] = MOUSE;
                    status[i][j][MOUSE] = MOUSE;
                    q.push({i, j, CAT});
                    q.push({i, j, MOUSE});
                }else if(i == j){
                    status[i][j][CAT] = CAT;
                    status[i][j][MOUSE] = CAT;
                    q.push({i, j, CAT});
                    q.push({i, j, MOUSE});
                }else{
                    outDegree[i][j][MOUSE] = graph[j].size();
                    //如果当前这个地方状态是不确定的 那么老鼠的回合还能走哪些状态的个数。但是对于猫而言 需要排除0的位置
                    for(auto k : graph[i]){
                        if(k != 0){
                            outDegree[i][j][CAT]++;
                        }
                    }
                }
            }
        }
        while(!q.empty()){
            int len = q.size();
            while(len){
                auto t = q.front(); q.pop(); len--;
                int m_pos = t.m_pos;
                int turn = t.turn;
                int c_pos = t.c_pos;
                if(status[c_pos][m_pos][turn] == 0) continue;//还没有结果 无法为下面的状态染色
                if(turn == MOUSE){
                    //老鼠的回合，这一轮状态已经确定了，那么前一轮就是猫的回合，看看猫会怎么走，哪些状态能够被染色
                    for(auto x : graph[c_pos]){//这里是看猫能走哪些
                        if(x == 0) continue;//猫肯定不能走0
                        if(status[x][m_pos][CAT] != 0) continue;//下面的一局情况已经确定 这里我们是给每个节点染色 并不不是去找是否会胜利
                        
                        if(status[c_pos][m_pos][turn] == CAT){//当前的这个状态一定是要么cat 要么mouse 所以是确定的
                            //当前的状态是猫获胜，猫肯定会走这里
                            status[x][m_pos][CAT] = CAT;
                            q.push({x, m_pos, CAT});
                        }else{
                            //当前的状态是老鼠获胜，说明什么，说明猫一定会尽力避免这种状态， 也就是
                            outDegree[x][m_pos][CAT]--;//也就是猫在x的位置，老鼠在m——pos，然后是cat的回合 也就是上一轮 肯定不能走这里，
                            if(outDegree[x][m_pos][CAT] == 0){//猫已经无路可走了
                                status[x][m_pos][CAT] = MOUSE;
                                q.push({x, m_pos, CAT});
                            }
                        }
                    }
                }else{//turn = CAT, 和turn = MOUSE类似
                    for(auto x : graph[m_pos]){
                        if(status[c_pos][x][MOUSE] != 0) continue;//已经被染色
                        if(status[c_pos][m_pos][turn] == MOUSE){//这一轮是老鼠胜利，上一轮是老鼠轮，那么他肯定会走这里
                            status[c_pos][x][MOUSE] = MOUSE;
                            q.push({c_pos, x, MOUSE});
                        }else{//上一把老鼠会尽力避免走到这里
                            outDegree[c_pos][x][MOUSE]--;
                            if(outDegree[c_pos][x][MOUSE] == 0){
                                status[c_pos][x][MOUSE] = CAT;
                                q.push({c_pos, x, MOUSE});
                            }
                        }
                    }
                }
            }
        }
        return status[CAT][MOUSE][MOUSE];
    }
};
