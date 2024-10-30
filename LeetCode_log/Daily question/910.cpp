#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int smallestRangeII(vector<int>& nums, int k) {
    ranges::sort(nums);
    int ans = nums.back() - nums[0],maxi,mini;
    for(int i = 1;i < nums.size();++ i)
    {
        maxi = max(nums[i - 1] + k,nums.back() - k);
        mini = min(nums[0] + k,nums[i] - k);
        ans = min(ans,maxi - mini);
    }
    return ans;
}