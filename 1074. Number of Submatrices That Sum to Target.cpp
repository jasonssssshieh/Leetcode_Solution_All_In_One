https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/description/
类似LC560这个题

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        //参考leetcode 560的解法
        //95.60% perfect
        if(matrix.empty()) return 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> preSumMatrix(m, vector<int>(n, 0));
        for(int i = 0; i < m; ++i){
            preSumMatrix[i][0] = matrix[i][0];
            for(int j = 1; j < n; ++j){
                preSumMatrix[i][j] = preSumMatrix[i][j-1] + matrix[i][j];
            }
        }
        int res = 0;
        //然后我们任意取两列, 比如第col1和col2列, 那么对于包括这两列在内的区域, 我们对于每一行,都去检查 看能不能找到某个区域的值是target的,这里我们是把行固定
        unordered_map<int, int> mp;
        for(int col1 = 0; col1 < n; ++col1){
            for(int col2 = col1; col2 < n; ++col2){//这里col2是从col1开始的  因为可以只有单独的一个cell
                mp[0] = 1;
                int sum = 0;
                for(int i = 0; i < m; ++i){
                    sum += preSumMatrix[i][col2] - (col1 == 0 ? 0 : preSumMatrix[i][col1-1]);
                    int t = sum - target;
                    if(mp.count(t)){
                         res += mp[t];
                    }
                    mp[sum]++;
                }
                mp.clear();
            }
        }
        return res;
    }
};
