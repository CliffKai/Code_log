/*
拼多多 - 2024/10/19
1. 最长山脉
把符合下列属性的数组 arr 称为 山脉数组 ：
- arr.length >= 3
- 存在下标 i（0 < i < arr.length - 1），满足
  - arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
  - arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
给出一个整数数组 arr，返回最长山脉子数组的长度。如果不存在山脉子数组，返回 0 。
 
示例 1：
输入：arr = [2,1,4,7,3,2,5]
输出：5
解释：最长的山脉子数组是 [1,4,7,3,2]，长度为 5。
示例 2：
输入：arr = [2,2,2]
输出：0
解释：不存在山脉子数组。

OJ:https://leetcode-cn.com/problems/longest-mountain-in-array/description/
*/
#include<iostream>
#include<vector>

using namespace std;

int longestMountain(vector<int>& arr) {
    int n = arr.size();
    int ans = 0,pre = 1;
    bool signr = false,signf = false;
    for(int i = 1;i < n;++ i)
    {
        if(arr[i] > arr[i - 1])
        {
            if(signr)
            {
                ++ pre;
            }
            else
            {
                signf = false;
                pre = 2;
                signr = true;
            }
        }
        else if(arr[i] == arr[i - 1])
        {
            signr = false,signf = false;
            pre = 1;
        }
        else
        {
            if(signf)
            {
                ++ pre;
                ans = max(ans,pre);
            }
            else
            {
                if(signr)
                {
                    signr = false;
                    signf = true;
                    ++ pre;
                    ans = max(ans,pre);
                }
            }
        }
    }
    return ans;
}

int main()
{
    vector<int> arr = {2,1,4,7,3,2,5};
    cout << longestMountain(arr) << endl;

    system("pause");

    return 0;
}