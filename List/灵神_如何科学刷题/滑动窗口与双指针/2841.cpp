#include<iostream>
#include<vector>

using namespace std;

long long fun(vector<int> & nums,unordered_map<int,int> & hash,int pre,int s,int k)
{
    -- hash[nums[s - 1]];
    if(hash[nums[s - 1]] == 0)
    {
        -- pre;
        hash.erase(nums[s - 1]);
    }
    ++ hash[nums[s + k - 1]];
    if(hash[nums[s + k - 1]] == 1)
    {
        ++ pre;
    }
    return pre;
}

long long maxSum(vector<int>& nums, int m, int k) {
    unordered_map<int,int> hash;
    long long ans = 0,pre_s = 0,pre_n = 0,n = nums.size();
    for(int i = 0;i < k;++ i)
    {
        if(hash[nums[i]] == 0)
        {
            ++ pre_n;
        }
        ++ hash[nums[i]];
        pre_s += nums[i];
    }
    if(pre_n >= m)
    {
        ans = pre_s;
    }
    for(int i = 1;i < n - k + 1;++ i)
    {
        pre_s -= nums[i - 1];
        pre_s += nums[i + k - 1];
        pre_n = fun(nums,hash,pre_n,i,k);
        if(pre_n >= m)
        {
            ans = max(ans,pre_s);
        }
    }
    return ans;
}

int main()
{
    vector<int> nums = {1,2,3,4,5,6,7,8,9,10};
    int m = 3,k = 3;
    cout << maxSum(nums,m,k) << endl;
    return 0;
}