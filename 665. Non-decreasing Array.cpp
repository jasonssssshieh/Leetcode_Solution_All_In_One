
题目链接: https://leetcode.com/problems/non-decreasing-array/description/


class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        if(nums.size() < 3) return true;
        bool modify = false;
        /*
        分析:
        如果我们当前是在i=1的时候,违反了non-decreasing => nums[i] < nums[i-1]
        那么我们可以nums[i] = nums[i-1] 也可以nums[i-1] = nums[i]
        那么我认为就应该尽可能的让前面小,这样才能有可能保证后面的数能够满足非递减的性质=>
        所以我们把nums[i-1]设置为nums[i]. => nums[i-1] = nums[i]
        
        如果不是i=1的情况, 那么我们还需要考虑修改了nums[i-1]后 nums[i-2]和nums[i-1]的关系.
        如果nums[i] >= nums[i-2] 那么肯定要修改nums[i-1]了, 为啥不修改nums[i]呢 因为这时候修改nums[i] 只能是nums[i] 增加,这样就有可能导致后面的数字要求变高 所以这里我们采用降低前面的数字=> 这里把nums[i-1] = nums[i-2] or nums[i] 都是可以的 两个都能过.考虑代码简洁性, 我就采用了nums[i-1] = nums[i]这个
        
        如果nums[i] < nums[i-2] 那么我们肯定不能把nums[i-1]改成nums[i] 这样就会违反规律,所以这时,只能nums[i] = nums[i-1]
        */
        for(int i = 1; i < nums.size(); ++i){
            if(nums[i] >= nums[i-1]) continue;
            if(modify) return false;
            modify = true;
            if(i == 1 || nums[i] >= nums[i-2]){
                nums[i-1] = nums[i];
            }else{
                nums[i] = nums[i-1];
            }
        }
        return true;
    }
};
/*
test case: 
[4,2,3]
[4,2,1]
[4,3,1,2,3,4,5]
[2,3,3,2,4]
[-1,4,2,3]
[4,2,3]
*/
