#include <iostream>
#include <vector>

using namespace std;

//方法3：双指针
int trap(vector<int>& height) 
{
    int r = height.size() - 1,l = 0,rm = 0,lm = 0,ans = 0;
    while(l < r)
    {
        lm = max(lm,height[l]);
        rm = max(rm,height[r]);
        if(height[l] < height[r])
        {
            ans += lm - height[l];
            ++ l;
        }
        else
        {
            ans += rm - height[r];
            -- r;
        }
    }
    return ans;
}

// 方法2：单调栈

// 方法1：双指针
// int trap(vector<int>& height) 
// {
//     int n = height.size(),ans = 0;
//     vector<int> l(n),r(n);
//     l[0] = height[0],r[n - 1] = height[n - 1];
//     for(int i = 1;i < n;++ i)
//     {
//         if(height[i] > l[i - 1])
//         {
//             l[i] = height[i];
//         }
//         else
//         {
//             l[i] = l[i - 1];
//         }
//         if(height[n - 1 - i] > r[n - i])
//         {
//             r[n - 1 - i] = height[n - 1 - i];
//         }
//         else
//         {
//             r[n - 1 - i] = r[n - i];
//         }
//     }
//     for(int i = 0;i < n;++ i)
//     {
//         ans += (min(l[i],r[i]) - height[i]) > 0 ? min(l[i],r[i]) - height[i]:0;
//     }
//     return ans;
// }

int main()
{
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << trap(height) << endl;
    return 0;
}