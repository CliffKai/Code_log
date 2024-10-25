/*
2. 搜索二维数组 (要求两种解法）
在一个二维数组array中（每个一维数组的长度相同）， 每一行都按照 从左到右递增的顺序排序， 每一列都按照 从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

示例 1：
二维数组：
1   3   4   5
2  6   7    9
4  8  10  13
7  10 15  20
输入：二维数组，目标数值: 13
输出：true
OJ:https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/description/
*/
#include <iostream>
#include <vector>

using namespace std;

// 方法1:逐行二分查找
// 不作说明

// 方法2:从右上角开始查找(相当于同时利用了行和列的递增性质)
bool find(vector<vector<int>>& plants, int target,int i,int j)
{
    if(i >= plants.size()  || j < 0)
    {
        return false;
    }
    if(plants[i][j] == target)
    {
        return true;
    }
    else if(plants[i][j] > target)
    {
        return find(plants, target, i, j - 1);
    }
    else
    {
        return find(plants,  target, i + 1, j);
    }
}

bool findTargetIn2DPlants(vector<vector<int>>& plants, int target) {
    if(plants.size() == 0)
    {
        return false;
    }
    return find(plants,target,0,plants[0].size() - 1);
}

int main()
{
    vector<vector<int>> plants = {{1,3,4,5},{2,6,7,9},{4,8,10,13},{7,10,15,20}};
    int target = 13;
    cout << findTargetIn2DPlants(plants,target) << endl;
    return 0;
}