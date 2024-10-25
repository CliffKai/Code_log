#include <iostream>
#include <vector>

using namespace std;

int jump(vector<int> &nums,int i)
{
    int pre = 0, max = nums[0], sum = 0, jump = 0;
    while (pre + nums[pre] < nums.size() - 1)
    {
        for (int i = 0; i < nums[pre]; ++i)
        {
            if (pre + nums[pre + i] + i >= max)
            {
                max = pre + nums[pre + i] + i;
                jump = pre + i;
            }
        }
        ++sum;
        pre = jump;
        max = nums[pre];
    }
    return sum;
}

int jump(vector<int> &nums)
{
    int maxPos = 0, n = nums.size(), end = 0, step = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        if (maxPos >= i)
        {
            maxPos = max(maxPos, i + nums[i]);
            if (i == end)
            {
                end = maxPos;
                ++step;
            }
        }
    }
    return step;
}

int main()
{
    vector<int> arr({7, 1, 1, 1, 1, 1, 1, 7, 7});
    cout << jump(arr) << endl;
    system("pause");
    return 0;
}