#include<iostream>
#include<vector>

using namespace std;

int main()
{
    vector<int> nums = {1,2,3,4};
    vector<int> ans = productExceptSelf(nums);
    for(int i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

vector<int> productExceptSelf(vector<int>& nums) 
{
    int n = nums.size(),tmp = 1;
    vector<int> ans(n,1);
    for(int i = 1;i < n;++ i)
    {
        ans[i] = ans [i - 1] * nums[i - 1];
    }
    for(int i = n - 2;i >= 0;-- i)
    {
        tmp *= nums[i + 1];
        ans[i] *= tmp;
    }
    return ans;
}