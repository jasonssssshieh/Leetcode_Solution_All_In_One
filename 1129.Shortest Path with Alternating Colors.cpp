/*
https://leetcode.com/problems/shortest-path-with-alternating-colors/description/
寻找从0开始到每一个点的最短距离,并且这个path必须是color alternative的
BFS
同时每次visit某个节点的位置的时候 需要考虑red和blue两条edge.

*/

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        vector<int> res(n, -1);
        res[0] = 0;
        unordered_map<int, unordered_set<int>> redEdges;
        unordered_map<int, unordered_set<int>> blueEdges;
        for(auto v : red_edges){
            redEdges[v[0]].insert(v[1]);
        }
        for(auto v : blue_edges){
            blueEdges[v[0]].insert(v[1]);
        }
        queue<vector<int>> q;
        q.push({0, 0});//index, last color, distance.
        vector<int> visited(n, 0);
        visited[0] = 1;
        int step = 1;
        while(!q.empty()){
            int len = q.size();
            while(len){
                auto v = q.front(); q.pop(); len--;
                if(v[1] != 1){
                    //red = 1
                    for(auto p : redEdges[v[0]]){
                        if((visited[p]&1)) continue;
                        res[p] = res[p] == -1 ? step : res[p];
                        q.push({p, 1});
                        visited[p] = visited[p] | 1;
                    }
                }
                if(v[1] != -1){
                    //blue = -1
                    for(auto p : blueEdges[v[0]]){
                        if((visited[p]&2)) continue;
                        res[p] = res[p] == -1 ? step : res[p];
                        q.push({p, -1});
                        visited[p] = visited[p] | 2;
                    }
                }
            }
            step++;
        }
        return res;
    }
