#include <iostream>
#include <vector>

using namespace std;

int jump(vector<int> &nums)
{
    int pre = nums[0] - 1, i, j, jumpi, jumpj, sum = 0;
    for (i = 1; i < nums.size(); ++i)
    {
        if ((i + pre) >= nums.size() - 1)
        {
            sum++;
            break;
        }
        else
        {
            jumpi = i;
            jumpj = pre;
            for (j = 1; j <= nums[i]; ++j)
            {
                if (nums[i + j] + i > (jumpj + i))
                {
                    jumpi = i + j;
                    jumpj = nums[jumpi];
                }
            }
            i = jumpi;
            pre = jumpj;
            sum++;
        }
    }
    return sum;
}

int main()
{
    vector<int> arr({2, 3, 1, 1, 4});
    cout << jump(arr) << endl;
    system("pause");
    return 0;
}