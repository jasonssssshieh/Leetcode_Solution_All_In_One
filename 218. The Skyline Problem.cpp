题目链接： https://leetcode.com/problems/the-skyline-problem/description/
著名的神仙题。博主第一次看到这个题也是直接放弃，后来看了很久的solution才明白到底是怎么一回事。
这道题意思就是给定了一系列的vector<int>， 代表了每一个大厦的起点，终点和高度。然后输出天际线的轮廓。
扫描线思路：
进入某个新的大楼的时候，如果当前的最高的高度是新的大楼的高度，那么我们需要记录下这个最高的点（进入点和高度），否则是不记录的。
如果是退出某个大楼，会使得当前的最高高度改变，那么这个退出点（以及高度）也是需要被记录的。
这道题的Corner case：
1. 在进入某个大楼的时候，有两个或者以上的大楼左边重叠，并且新的最高楼高度大于原来的最高高度，那么我们只记录那个最高的楼的。
2. 在退出某个大楼的时候，有两个或者以上的大楼右边重叠，并且新的最高楼高度小于原来的最高高度，那么我们只记录那个最低的楼的。

这里我们自己定义个event类，进入一个大楼是一个event，离开一个大楼也是一个新的event：
class event{
public:
    event(int x, int height, int status){
        this->x = x;//代表位置，也就是大楼的起点或者终点
        this->h = height;//大楼的高度
        this->status = status;//进入 = 1，离开 = -1
    }
    int h;
    int x;
    int status;
};

排序规则是按照首先x从小到大排列，因为我们是从左往右扫描。x相同的情况下，我们根据上面的规则：
class compare{
public:
    bool operator()(event* a, event* b){
        if(a->x != b->x) return a->x < b->x;
        //出去的时候高度高的排在后面，进入的时候 高度高的排在前面
        return a->h * a->status > b->h * b->status;
    }
};
另外，我们需要每次都记录一下当前的最高高度，这里我使用tree set，由于高度可能有重复，这里直接用c++ STL的multiset (使用priority_queue也是可行的)

代码如下：

//建立自己的event类
class event{
public:
    event(int x, int height, int status){
        this->x = x;
        this->h = height;
        this->status = status;
    }
    int h;
    int x;
    int status;
};

//event类的排序规则
class compare{
public:
    bool operator()(event* a, event* b){
        if(a->x != b->x) return a->x < b->x;
        //出去的时候高度高的排在后面，进入的时候 高度高的排在前面
        return a->h * a->status > b->h * b->status;
    }
};

class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        if(buildings.empty()) return {};
        vector<event*> vec;
        //对于所有的building 我们都构建两个event类对象，也就是进入和出去
        for(auto b : buildings){
            auto e1 = new event(b[0], b[2], 1);
            auto e2 = new event(b[1], b[2], -1);
            vec.push_back(e1);
            vec.push_back(e2);
        }
        //对所有的event类对象进行排序
        sort(vec.begin(), vec.end(), compare());
        
        //multiset用来记录记录最大高度，这里是从大到小排列的顺序。
        multiset<int, greater<int>> heights;
        //起始位置的高度为0.
        heights.insert(0);
        int curMaxHeight = 0;
        vector<pair<int, int>> res;
        for(auto e : vec){
            if(e->status == 1){//如果是进入事件，也就是我们现在要进入一个新的building，那么我们要看看他是否刷新了当前的最高高度
                heights.insert(e->h);
                if(curMaxHeight < *heights.begin()){//如果刷新的最高高度，那就是我们需要记录的位置，放在结果的vector里面
                    curMaxHeight = *heights.begin();
                    res.push_back({e->x, curMaxHeight});
                }
            }else{
                //如果是进入事件，也就是我们现在要离开某一个building，首先我们要从multiset里删除这个building的高度，
                //然后再看看当前这个building的高度是否是唯一最高的，如果是，那么就需要修改当前最高高度，并且这个点也是需要push进入结果的。
                auto itr = heights.lower_bound(e->h);//这里不能直接erase e->h 因为multiset中直接erase某个value会把所有的这个value都删除，这里需要用iterator来操作。
                heights.erase(itr);
                if(curMaxHeight > *heights.begin()){
                    curMaxHeight = *heights.begin();
                    res.push_back({e->x, curMaxHeight});
                }
            }
        }
        return res;
    }
};
