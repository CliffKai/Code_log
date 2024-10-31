#include <iostream>
#include <vector>

using namespace std;

double findMaxAverage(vector<int>& nums, int k) {
    int n = nums.size(),pre = 0,ans = 0;
    for(int i = 0;i < k;++ i)
    {
        pre += nums[i];
    }
    ans = pre;
    for(int i = k;i < n;++i)
    {
        pre -= nums[i - k];
        pre += nums[i];
        ans = max(ans,pre);
    }
    return ans * 1.0 / k;
}

int main()
{
    vector<int> nums = {1,12,-5,-6,50,3};
    int k = 4;
    cout << findMaxAverage(nums,k) << endl;
    return 0;
}