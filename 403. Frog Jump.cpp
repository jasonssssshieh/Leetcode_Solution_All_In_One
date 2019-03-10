题目链接：https://leetcode.com/problems/frog-jump/description/
🐸青蛙跳
青蛙站在index = 0的位置，第一次起跳必须跳1步；其余的位置，假如现在青蛙上一次跳了k步，那么当前这一次就只能跳k-1, k, k+1步
然后vector<int>& stones里面代表了每个stone的位置，如果没法跳到对应的位置，算失败。问最后能不能跳到最后一块石头上。
非常明显的DP问题了。
我们对于每一个位置，都可以记录一下走到当前这个position的步数，那么走下一步的时候，就能按照上一步的步数来走，hash map + hash set即可。

class Solution {
public:
    bool canCross(vector<int>& stones) {
        if(stones.size() < 2) return true;
        //If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.
        //就是根据上一步的步数来确定下一步的步数 很明显的dp
        unordered_map<int, unordered_set<int>> mp;
        for(auto num : stones){
            mp[num] = unordered_set<int>();
        }
        mp[0] = {0};
        int target = stones.back();
        for(int i = 0; i < stones.size(); ++i){
            if(mp.count(stones[i]) == 0) return false;
            for(auto k : mp[stones[i]]){
                if(k - 1 > 0){
                    if(mp.count(stones[i] + k - 1)) mp[stones[i] + k - 1].insert(k-1);
                }
                if(k > 0){
                    if(mp.count(stones[i] + k)) mp[stones[i] + k].insert(k);
                }
                if(k + 1 > 0){
                    if(mp.count(stones[i] + k + 1)) mp[stones[i] + k + 1].insert(k + 1);
                }
                if(mp[target].size()) return true;
            }
        }
        return mp[target].size();
    }
};
