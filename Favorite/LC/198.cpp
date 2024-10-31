//动态规划学习的不二之选
//非常推荐这个题解：https://leetcode.cn/problems/house-robber/solutions/138131/dong-tai-gui-hua-jie-ti-si-bu-zou-xiang-jie-cjavap/

#include<iostream>
#include<vector>

using namespace std;

//动态规划:空间复杂度O(n)
// int rob(vector<int>& nums) {
//     int n = nums.size();
//     vector<int> f(n + 1,0);
//     f[0] = 0;
//     f[1] = nums[0];
//     for(int i = 2;i <= n;++ i)
//     {
//         f[i] = max(f[i - 1],f[i - 2] + nums[i - 1]);
//     }
//     return f[n];
// }

//动态规划:空间复杂度O(1)
int rob(vector<int>& nums) {
    int n = nums.size();
    int i_1 = nums[0],i_2 = 0;
    int ans = i_1;
    for(int i = 2;i <= n;++ i)
    {
        ans = max(i_1,i_2+ nums[i - 1]);
        i_2 = i_1;
        i_1 = ans;
    }
    return ans;
}

int main()
{
    vector<int> nums = {2,7,9,3,1};
    cout << rob(nums) << endl;
    return 0;
}
