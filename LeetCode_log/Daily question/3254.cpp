#include <iostream>
#include <vector>

using namespace std;

vector<int> resultsArray(vector<int> &nums, int k)
{
    if(k == 1)
    {
        return nums;
    }
    int n = nums.size(), sign = -1;
    vector<int> ans;
    for (int i = 1; i < k; ++i)
    {
        if (nums[i] == nums[i - 1] + 1)
        {
            continue;
        }
        else
        {
            sign = i - 1;
        }
    }
    if (sign >= 0)
    {
        ans.push_back(-1);
    }
    else
    {
        ans.push_back(nums[k - 1]);
    }
    for (int i = k; i < n; ++i)
    {
        if (sign >= i - k + 1 && sign <= i)
        {
            ans.push_back(-1);
            if (nums[i] != nums[i - 1] + 1)
            {
                sign = i - 1;
            }
        }
        else
        {
            if (nums[i] == nums[i - 1] + 1)
                ans.push_back(nums[i]);
            else
            {
                ans.push_back(-1);
                sign = i - 1;
            }
        }
    }
    return ans;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 3;
    vector<int> ans = resultsArray(nums, k);
    for (int i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}