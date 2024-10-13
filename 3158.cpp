#include<iostream>
#include<vector>

using namespace std;

int main()
{
    vector<int> nums = {4,3,2,7,8,2,3,1};
    cout << duplicateNumbersXOR(nums) << endl;
    return 0;
}

int duplicateNumbersXOR(vector<int>& nums) {
    int ans = 0;
    long long hash = 0;
    for(int i : nums)
    {
        if(hash >> i & 1)
        {
            ans ^= i;
        }
        else
        {
            hash |= 1LL << i;
        }
    }
    return ans;
}
