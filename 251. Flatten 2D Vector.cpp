题目链接:https://leetcode.com/problems/flatten-2d-vector/description/
By using iterator

class Vector2D {
public:
    vector<vector<int>>::iterator itr_vec_vec;
    vector<vector<int>>::iterator itr_vec_vec_end;
    vector<int>::iterator itr;
    vector<int>::iterator itr_end;
    Vector2D(vector<vector<int>>& v) {
        itr_vec_vec = v.begin();
        itr_vec_vec_end = v.end();
        if(!v.empty()){
            itr = (*itr_vec_vec).begin();
            itr_end = (*itr_vec_vec).end();
        }
    }
    
    int next() {
        //if(itr == itr_end) cout<<"error!"<<endl;
        int res = *itr;
        itr = std::next(itr, 1);
        //天坑地缝之有可能这个vector是空的
        hasNext();
        return res;
    }
    
    bool hasNext() {
        while(itr_vec_vec != itr_vec_vec_end){
            if(itr == itr_end){
                itr_vec_vec++;
                if(itr_vec_vec == itr_vec_vec_end) break;
                itr = (*itr_vec_vec).begin();
                itr_end = (*itr_vec_vec).end();
            }else{
                break;
            }
        }
        return !(itr_vec_vec == itr_vec_vec_end);
    }
};
/*
["Vector2D","next","next","next","hasNext","hasNext","next","hasNext"]
[[[[1,2],[3],[4]]],[null],[null],[null],[null],[null],[null],[null]]
["Vector2D","next","next","next","hasNext","hasNext","next","hasNext"]
[[[[1,2],[5],[4]]],[null],[null],[null],[null],[null],[null],[null]]
["Vector2D","hasNext","next","hasNext"]
[[[[],[3]]],[null],[null],[null]]
*/
/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(v);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
