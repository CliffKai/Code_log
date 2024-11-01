#include<iostream>
#include<vector>

using namespace std;

vector<int> getAverages(vector<int>& nums, int k) {
    int n = nums.size();
    long long med = 0;
    vector<int> ans(n,-1);
    for(int i = 0;i < 2 * k && i < n;++ i)
    {
        med += nums[i];
    }
    for(int i = 2 * k;i < n;++ i)
    {
        med += nums[i];
        ans[i - k] = med / (2 * k + 1);
        med -= nums[i - 2 * k];
    }
    return ans;
}

int main()
{
    vector<int> nums = {1,2,3,4,5,6,7,8,9,10};
    int k = 2;
    vector<int> ans = getAverages(nums,k);
    for(int i = 0;i < ans.size();++ i)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}