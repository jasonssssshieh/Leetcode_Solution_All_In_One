题目链接： https://leetcode.com/problems/range-sum-query-2d-mutable/description/
升级加强版 这个题目的思路还是binary index tree
由于我们的input变成了2-d的matrix，所以对于每一行我们都建立一个binary index tree即可。
另外，这题目特别阴险的就是有空的matrix传入（非常无语的test case）
["NumMatrix"]
[[[]]]

class BinaryIndexTree{
public:
    vector<vector<int>> sum;
    BinaryIndexTree(int m, int n){
        sum.resize(m, vector<int>(n+1, 0));
    }
    
    void update(int i, int j, int delta){
        if(delta == 0) return;
        while(j < sum[i].size()){
            sum[i][j] += delta;
            j += bitwise(j);
        }
        return;
    }
    
    int query(int i, int j){
        int res = 0;
        while(j > 0){
            res += sum[i][j];
            j -= bitwise(j); 
        }
        return res;
    }
    
    int bitwise(int i){return i & (-i);}
    
};

class NumMatrix {
public:
    BinaryIndexTree* root;
    vector<vector<int>> matrix_;
    NumMatrix(vector<vector<int>> matrix) {
        matrix_ = matrix;
        if(!matrix.empty()){
            root = new BinaryIndexTree(matrix.size(), matrix[0].size());
            update();
        }
    }
    
    void update(){
        for(int i = 0; i < matrix_.size();++i){
            for(int j = 0; j < matrix_[i].size(); ++j){
                root->update(i, j + 1, matrix_[i][j]);
            }
        }
    }
    
    void update(int row, int col, int val) {
        if(matrix_.empty()) return;
        int delta = val- matrix_[row][col];
        matrix_[row][col] = val;
        root->update(row, col+1, delta);
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        if(matrix_.empty()) return 0;
        int res = 0;
        for(int i = row1; i <= row2; ++i){
            res += root->query(i, col2+1) - root->query(i, col1);
        }
        return res;
    }
};
