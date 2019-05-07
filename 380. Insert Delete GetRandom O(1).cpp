题目链接:https://leetcode.com/problems/insert-delete-getrandom-o1/description/

这个题目要求我们设计一个叫做RandomizedSet的class,其中三个操作: insert, remove,getRandom 都是要O(1)的时间
这里我们每次加入的数都是unique的,没有duplicate.大大降低了难度
insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
既然要O(1)的时间那么肯定要用hash map,这里我们设计的思路就是空间换时间
vector<int> vec; 用来记录整个val的向量
unordered_map<int, int> mp; 是val和这个val在上面vec里的index位置.
如果插入一个新的数,我们就push进vec的尾部, 并且在mp里记录他的index
删除一个数,那么就首先和vec尾部的数交换,然后更新尾部那个元素的index, 然后删除当前尾部的元素(也就是要remove 的那个val).最后在hash map里erase掉val即可.
getRandom就直接在我们vec里随机选择一个index,返回vec[index]即可.



class RandomizedSet {
public:
    /** Initialize your data structure here. */
    vector<int> vec;
    unordered_map<int, int> mp; //index
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(mp.count(val)){
            return false;
        }
        mp[val] = vec.size();
        vec.push_back(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(!mp.count(val)) return false;
        int idx = mp[val];
        int last_val = vec.back();
        int last_idx = mp[last_val];
        swap(vec[last_idx], vec[idx]);
        vec.pop_back();
        mp[last_val] = idx;
        mp.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        if(vec.empty()) return -1;
        int idx = random()%vec.size();
        return vec[idx];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
/*
["RandomizedSet","insert","remove","insert","getRandom","remove","insert","getRandom"]
[[],[1],[2],[2],[],[1],[2],[]]
["RandomizedSet","insert","insert","remove","insert","remove","getRandom"]
[[],[0],[1],[0],[2],[1],[]]
["RandomizedSet","remove","remove","insert","getRandom","remove","insert"]
[[],[0],[0],[0],[],[0],[0]]
*/
