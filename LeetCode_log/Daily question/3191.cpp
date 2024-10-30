#include<iostream>
#include<vector>

using namespace std;

int minOperations(vector<int>& nums) {
    int ans = 0,n = nums.size();
    for(int i = 0;i < n - 2;++ i)
    {
        if(nums[i] == 0)
        {
            nums[i + 1] ^= 1;
            nums[i + 2] ^= 1;
            ++ ans;
        }
    }
    if(nums[n - 1] == 1 && nums[n - 2] == 1)
    {
        return ans;
    }
    return -1;
}

int main()
{
    vector<int> nums = {1,0,0,1,0,1};
    cout << minOperations(nums) << endl;
    return 0;
}