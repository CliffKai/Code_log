#include <bits/stdc++.h>

using namespace std;


double minimumAverage(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(),nums.end());
    int ans = nums[0] + nums[n - 1];
    for(int i = 1;i / 2 < n / 2;++ i)
    {
        ans = min(ans,(nums[i] + nums[n - i - 1]));
    }
    return ans / 2.0;
}

int main()
{
    vector<int> nums = {3,7,5,6,4,2};
    cout << minimumAverage(nums) << endl;
    return 0;
}