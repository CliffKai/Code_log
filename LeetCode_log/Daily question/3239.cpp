#include<iostream>
#include<vector>

using namespace std;

int minFlips(vector<vector<int>>& grid) {
    int ansl = 0,ansr = 0,n = grid.size(),m = grid[0].size();
    for(int i = 0;i < n;++ i)
    {
        for(int j = 0;j < m / 2;++ j)
        {
            ansr += grid[i][j] != grid[i][m - 1 - j];
        }
    }
    for(int j = 0;j < m;++ j)
    {
        for(int i = 0;i < n / 2;++ i)
        {
            ansl += grid[i][j] != grid[n - 1 -i][j];
        }
    }
    return min(ansl,ansr);
}

int main()
{
    vector<vector<int>> grid = {{0,0,0},{0,0,0}};
    cout << minFlips(grid) << endl;
    return 0;
}