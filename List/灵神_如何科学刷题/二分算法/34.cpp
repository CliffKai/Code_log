#include<iostream>
#include<vector>

using namespace std;

int stri(vector<int> nums,int target,int str,int end)
{
    if(str == end)
    {
        return str;
    }
    if(nums[(str + end) / 2] < target)
    {
        return stri(nums,target,(str + end) / 2 + 1,end);
    }
    else
    {
        return stri(nums,target,str,(str + end) / 2);
    }
}
int endi(vector<int> nums,int target,int str,int end)
{
    if(str == end)
    {
        return str;
    }
    if(nums[(str + end) / 2 + 1] <= target)
    {
        return endi(nums,target,(str + end) / 2 + 1,end);
    }
    else
    {
        return endi(nums,target,str,(str + end) / 2);
    }
}

vector<int> searchRange(vector<int>& nums, int target) {
    if(nums.size() == 0)
    {
        return {-1,-1};
    }
    int str = stri(nums,target,0,nums.size() - 1),end = endi(nums,target,0,nums.size() - 1);
    if(nums[str] == target)
    {
        return {str,end};
    }
    else
    {
        return {-1,-1};
    }
}

int main()
{
    vector<int> nums = {5,7,7,8,8,10};
    int target = 8;
    vector<int> ans = searchRange(nums, target);
    cout << ans[0] << " " << ans[1] << endl;
    return 0;
}
