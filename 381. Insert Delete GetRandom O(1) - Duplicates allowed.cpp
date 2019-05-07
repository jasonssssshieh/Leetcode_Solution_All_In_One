题目链接 https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/description/

380. Insert Delete GetRandom O(1)的升级版本.现在我们放宽了条件, 也就是允许有重复元素. 
题目难度增加了, 既然要求全部o(1)的时间,那么一定是空间换时间. 大体思路还是380一样, 
vector<int> vec; 用来存所有的数字,因为我们需要random取数字,所以这里只能牺牲空间复杂度, 把所有数都存在vector里,然后随机根据index来返回对应的val.
只是这里我们原来的hash map需要改成:
unordered_map<int, unordered_set<int>> mp; val-val在vector里的所有的位置,这里用hash set就是方便O(1)时间查找和删除对应的index
代码如下:

class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    unordered_map<int, unordered_set<int>> mp;//用空间换时间. hash set里储存在val在vec里的index信息
    vector<int> vec;
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        mp[val].insert(vec.size());
        vec.push_back(val);
        return mp[val].size() == 1;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if(!mp.count(val)) return false;
        if(vec.back() != val){
            int idx = *(mp[val].begin());
            int last_element = vec.back();
            int last_idx = vec.size()-1;
            swap(vec[idx], vec[last_idx]);
            mp[last_element].erase(last_idx);
            mp[last_element].insert(idx);
            mp[val].erase(idx);
            mp[val].insert(last_idx);
        }
        mp[val].erase(vec.size()-1);
        if(mp[val].empty()) mp.erase(val);
        vec.pop_back();
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        int idx = random()%vec.size();
        return vec[idx];
    }
};

提示: remove的哪里不能写成如下这种方式:

/*
        这里是有错误的,这里debug了很久,是因为这里的hash set的缘故.
        [-1,0,5,4,4]
        比如我现在element是4, 位置有3,4
        现在我last_element = 4, last_idx = 4
        idx = 3 时
        我按照下面的操作就是:
        vec[idx] = last_element; ==> [-1,0,5,4,4]
        vec.pop_back();==>[-1,0,5,4]
        mp[last_element].erase(last_idx); ==> mp[4] = {3}
        mp[last_element].insert(idx); ==> mp[4] = {3}
        mp[val].erase(idx); ==> mp[4] = {}
        发现没有? 因为hash set会把重复的元素只计算一次 所以这里一定要判断一下是否为最后末尾元素 如果是就直接pop掉就好.!
        
        int last_idx = vec.size()-1;
        int last_element = vec[last_idx];
        vec[idx] = last_element;
        vec.pop_back();
        mp[last_element].erase(last_idx);
        mp[last_element].insert(idx);
        mp[val].erase(idx);
        cout<<"size of val: "<<val<<" is "<<mp[val].size()<<endl;
        if(mp[val].empty()) mp.erase(val);
        */

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
/*
["RandomizedCollection","insert","insert","insert","getRandom","remove","getRandom"]
[[],[1],[1],[2],[],[1],[]]
["RandomizedCollection","insert","insert","remove","insert","remove","getRandom"]
[[],[0],[1],[0],[2],[1],[]]
["RandomizedCollection","insert","insert","insert","insert","insert","insert","remove","remove","remove","remove","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom"]
[[],[1],[1],[2],[1],[2],[2],[1],[2],[2],[2],[],[],[],[],[],[],[],[],[],[]]
["RandomizedCollection","insert","insert","insert","insert","insert","remove","remove","remove","remove"]
[[],[4],[3],[4],[2],[4],[4],[3],[4],[4]]
["RandomizedCollection","insert","insert","insert","insert","insert","insert","remove","remove","remove","remove","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom"]
[[],[10],[10],[20],[20],[30],[30],[10],[10],[30],[30],[],[],[],[],[],[],[],[],[],[]]
*/
