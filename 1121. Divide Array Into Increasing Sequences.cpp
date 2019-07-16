最近忙project 好久没好好写solution了. 
题目连接:https://leetcode.com/problems/divide-array-into-increasing-sequences/description/

这个题目给定了一个单调不减的数组, 以及一个数字K, 我们要判断能不能把这个数组重新组合成几个新的并且严格递增的sequences, 每个sequences的大小都是大于等于K
时间复杂度O(n)
空间复杂度O(1)
        /*
        我自己的第一想法就是每次我都尽可能的往那个最短的chunck里面塞数字, 然后如果不满足条件,再找下一个次短的... 最后判断是不是还有人没有达到长度为K.
        那么我们最少也需要有max frequency个sequences.  因为他的个数会直接影响新的sequence的开头 因此我们最少也要组成max frequency个sequences
        */
        
class Solution {
public:
    bool canDivideIntoSubsequences(vector<int>& nums, int K) {
        if(nums.empty() || K <= 0) return false;
        //non-decreasing array of positive integers  => sorted

        int maxFreq = 1;
        int count = 1;
        for(int i = 1; i < nums.size(); ++i){
            if(nums[i-1] == nums[i]){
                count++;
            }else{
                count = 1;
            }
            maxFreq = max(maxFreq, count);
        }
        return maxFreq*K <= nums.size();
        //这里我们如果说当前的nums的size是大于等于maxFreq*K(maxFreq*K是我们要求的最低的数组总共数字个数). 那么就可以返回true, 因为我们计算了maxFreq
            //就一定能够cover到所有的重复的情况, 并且保证每个sequences是递增的 因此只需要返回maxFreq*K和nums的size的大小比较即可
            //下面的判断都不需要了
            /*
        //maxFreq也就是我们这边最少数目的sequences的个数
        if(maxFreq * K > nums.size()) return false;//我们最少也需要maxFreq * K 个元素 如果不满足这个条件,肯定是不行的
        vector<int> ends(maxFreq, 0);
        for(int i = 0; i < nums.size(); ++i){
            bool flag = false;
            for(int j = 0; j < maxFreq; ++j){//我们就一个个的去试, 看看有没有能放进去成功的 一旦没成功就说明没办法满足了 return false
                if(ends[j] < nums[i]){
                    ends[j] = nums[i];
                    flag = true;
                    break;
                }
            }
            if(!flag) return false;
        }
        return true;
        */
    }
};
