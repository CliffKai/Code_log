/*
1. 乘积最大子数组
给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续 子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。测试用例的答案是一个 32-位 整数。
示例 1:
输入: nums = [2,3,-2,4]
输出: 6 解释: 子数组 [2,3] 有最大乘积 6。
示例 2:
输入: nums = [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
OJ:https://leetcode.cn/problems/maximum-product-subarray/description/
*/


#include<iostream>
#include<vector>

using namespace std;

int maxProduct(vector<int>& nums) {
    long maxi = nums[0],mini = nums[0],ans = nums[0];
    for(int i = 1;i < nums.size();++ i)
    {
        long mx = maxi,mn = mini;
        maxi = max(mx * nums[i],max((long)nums[i],mn * nums[i]));
        mini = min(mn * nums[i],min((long)nums[i],mx * nums[i]));

        ans = max(maxi,ans);
    }
    return ans;
}

int main()
{
    vector<int> nums = {2,3,-2,4};
    cout << maxProduct(nums) << endl;
    return 0;
}