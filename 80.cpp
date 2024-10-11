#include<iostream>

using namespace std;

int main()
{
    vector<int> nums = {1,1,1,2,2,3};
    cout << removeDuplicates(nums) << endl;
    return 0;
}

int removeDuplicates(vector<int>& nums) 
{
    int n = nums.size();
    if(n <= 2)
    {
        return n;
    }
    int s = 2,f = 2;
    while(f < n)
    {
        if(nums[s - 2] != nums[f])
        {
            nums[s] = nums[f];
            s ++;
        }
        f ++;
    }
    return s;
}