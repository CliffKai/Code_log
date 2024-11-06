#include<iostream>
#include<vector>

using namespace std;

int map[100005] = {0};

long long maximumSubarraySum(vector<int>& nums, int k) {
    long long int ans = 0,n = nums.size(),no = 0,sum = 0;
    for(int i = 0;i < k;++ i)
    {
        if(map[nums[i]] == 0)
        {
            ++ no;
        }
        ++ map[nums[i]];
        sum += nums[i];
    }
    if(no == k)
    {
        ans = sum;
    }
    for(int i = k;i < n;++ i)
    {
        sum -= nums[i - k];
        sum += nums[i];
        -- map[nums[i - k]];
        if(map[nums[i - k]] == 0)
        {
            -- no;
        }
        if(map[nums[i]] == 0)
        {
            ++ no;
        }
        ++ map[nums[i]];
        if(no == k)
        {
            ans = max(ans,sum);
        }
    }
    return ans;
}

int main()
{
    vector<int> nums = {1,2,1,2,3};
    int k = 2;
    cout << maximumSubarraySum(nums, k) << endl;
    return 0;
}