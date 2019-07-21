class Solution {
public:
    /*
    废话不多说, 这题先把绝对值展开:
    
    arr1[i] - arr1[j] + arr2[i] - arr2[j] + i - j
    arr1[i] - arr1[j] + arr2[j] - arr2[i] + i - j
    arr1[i] - arr1[j] + arr2[i] - arr2[j] + j - i
    arr1[i] - arr1[j] + arr2[j] - arr2[i] + j - i
    arr1[j] - arr1[i] + arr2[i] - arr2[j] + i - j
    arr1[j] - arr1[i] + arr2[j] - arr2[i] + i - j
    arr1[j] - arr1[i] + arr2[i] - arr2[j] + j - i
    arr1[j] - arr1[i] + arr2[j] - arr2[i] + j - i
    是不是头都大了? 来整理一下,把i放在一起, 把j 放在一起
    (arr1[i] + arr2[i] + i) - (arr1[j] + arr2[j] + j) 
    (arr1[i] - arr2[i] + i) - (arr1[j] - arr2[j] + j)
    (arr1[i] + arr2[i] - i) - (arr1[j] + arr2[j] - j)
    (arr1[i] - arr2[i] - i) - (arr1[j] - arr2[j] - j)
    -(arr1[i] - arr2[i] - i) + (arr1[j] - arr2[j] - j)
    .......
    看到上面的式子是不是有感觉了?找到规律没有?
    规律就是对于index = i的 我们看到的前面为正号的4个不同的情况(总共8个, 包括前面为负号的): 
    arr1[i] + arr2[i] + i, arr1[i] - arr2[i] + i, arr1[i] + arr2[i] - i, arr1[i] - arr2[i] - i
    实际上就是在每个式子就是在arr1[i] arr2[i] i 中间两个空隙插入+或者-号. 然后再对于这整个式子前面加一个负号或者正号 因此第一部分的4个式子就是:
    arr1[i] + arr2[i] + i
    arr1[i] - arr2[i] + i
    arr1[i] + arr2[i] - i
    arr1[i] - arr2[i] - i
    
   同理 对于index = j的 也有这样4个式子.而且符号都是对应相等的
    arr1[j] + arr2[j] + j
    arr1[j] - arr2[j] + j
    arr1[j] + arr2[j] - j
    arr1[j] - arr2[j] - j
    
    因此楼上的4个式子组合起来就是:
    (arr1[i] + arr2[i] + i) - (arr1[j] + arr2[j] + j) 
    (arr1[i] - arr2[i] + i) - (arr1[j] - arr2[j] + j)
    (arr1[i] + arr2[i] - i) - (arr1[j] + arr2[j] - j)
    (arr1[i] - arr2[i] - i) - (arr1[j] - arr2[j] - j)
    
    同时 交换i和j的位置 我们就得到了剩下的4个式子:
    -(arr1[i] + arr2[i] + i) + (arr1[j] + arr2[j] + j) 
    -(arr1[i] - arr2[i] + i) + (arr1[j] - arr2[j] + j)
    -(arr1[i] + arr2[i] - i) + (arr1[j] + arr2[j] - j)
    -(arr1[i] - arr2[i] - i) + (arr1[j] - arr2[j] - j)
    
    但本质上还是一样的,只是说谁做减数,谁做被减数的而已. 
    
    那么, 举个例子, 比如 (arr1[i] - arr2[i] - i), (arr1[j] - arr2[j] - j) 我们就有2种可能: (arr1[i] - arr2[i] - i) - (arr1[j] - arr2[j] - j) 
    和  (arr1[j] - arr2[j] - j) - (arr1[i] - arr2[i] - i)
    那么这两个结果里面取最大即可
    那么是不是也就等同于 maxValue of ((arr1[k] - arr2[k] - k)) - minValue of ((arr1[k] - arr2[k] - k)) for k = 0, ...., n-1
    
    因此 如果我们把
    arr1[k] + arr2[k] + k
    arr1[k] - arr2[k] + k
    arr1[k] + arr2[k] - k
    arr1[k] - arr2[k] - k
    计算出来, 得到4个vector
    
    然后对于每一个式子, 我们都有一个vector对于, 就能找到整个vector的最大值和最小值 我们都用它的最大值减去最小值, 就可以得到possible max Value, 然后取4个possible Max Value里面最大的值即可.
    
    */
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        int n =arr1.size();
        vector<int> a1(n, 0);
        vector<int> a2(n, 0);
        vector<int> a3(n, 0);
        vector<int> a4(n, 0);
        vector<int> minVal(4, INT_MAX);
        vector<int> maxVal(4, INT_MIN);
        for(int i = 0; i < n; ++i){
            a1[i] = arr1[i] + arr2[i] + i;
            a2[i] = arr1[i] + arr2[i] - i;
            a3[i] = arr1[i] - arr2[i] + i;
            a4[i] = arr1[i] - arr2[i] - i;
        }
        
        for(int i = 0; i < n; ++i){
            minVal[0] = min(a1[i], minVal[0]);
            minVal[1] = min(a2[i], minVal[1]);
            minVal[2] = min(a3[i], minVal[2]);
            minVal[3] = min(a4[i], minVal[3]);
            
            maxVal[0] = max(a1[i], maxVal[0]);
            maxVal[1] = max(a2[i], maxVal[1]);
            maxVal[2] = max(a3[i], maxVal[2]);
            maxVal[3] = max(a4[i], maxVal[3]);
        }
        int res = INT_MIN;
        for(int i = 0; i < 4;++i){
            res = max(res, maxVal[i] - minVal[i]);
        }
        return res;
    }
};
