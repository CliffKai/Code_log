#include<iostream>
#include<vector>

using namespace std;

int smallestRangeI(vector<int>& nums, int k) {
    int n = nums.size(),mini = 1e4,maxi = 0;
    for(int i = 0;i < n;++ i)
    {
        maxi = max(maxi,nums[i]);
        mini = min(mini,nums[i]);
    }
    return max(abs(maxi - mini) - 2 * k,0);
}

int main()
{
    vector<int> nums = {1,3,6};
    int k = 3;
    cout << smallestRangeI(nums,k) << endl;
    return 0;
}