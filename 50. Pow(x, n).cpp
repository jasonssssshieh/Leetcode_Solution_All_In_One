題目鏈接: https://leetcode.com/problems/powx-n/description/

   这个题目需要考虑的地方很多 正负号, 数据溢出 因为n是INT_MIN到INT_MAX里面的,所以如果INT_MIN取负号,就会溢出 但x好像正负号没有差
   cout<<(-3%2)<<endl; => 是-1 而不是1 n%2判断的时候要根据是不是=0来 而不是== 1来!!!
   下面是我自己寫的最簡潔的版本了
   基本思路就是2分法, 不斷的把n進行二分,另外n為奇數的時候 還需要多乘以一個x(n>0) 或者1/x(n<0)


class Solution {
public:
    double myPow(double x, int n) {
    //首先注意這裡如果n < 0 不能直接 return myPow(x, -n) 因為如果是INT_MIN取负号, 就會數據溢出.
        if(x == 0 || x == 1 || n == 1) return x;
        if(n == 0) return 1.0;
        if(n == -1) return 1/x;
        //上面三個是我們base case
        if(n%2 == 0){//如果n是偶數,那麼x正負都沒有關係了,所以直接取abs值.
            x = abs(x);
        }
        double res = myPow(x, n/2);
        return res*res*(n%2 != 0 ? (n < 0 ? 1.0/x : x) : 1);
    }
};
/*
2.00000
10
-13.62608
3
-1.00000
-2147483648
2.00000
-2147483648
1.00000
-2147483648
34.00515
-3
*/
