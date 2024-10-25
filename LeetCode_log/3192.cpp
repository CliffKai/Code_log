#include<iostream>
#include<vector>

using namespace std;

int minOperations(vector<int>& nums) {
    int sign = 0,n = nums.size(),ans = 0;
    for(int i = 0;i < n;++ i)
    {
        if(nums[i] ^ sign)
        {
            continue;
        }
        ++ ans;
        sign ^= 1;
    }
    return ans;
}

int main()
{
    vector<int> nums = {1,0,0,1,0,1};
    cout << minOperations(nums) << endl;
    return 0;
}
