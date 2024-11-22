#include <iostream>
#include <vector>

using namespace std;

int sign[301][301] = {0};
void BFS(vector<vector<char>>& grid, int i, int j, int m, int n) {
    sign[i][j] = 1;
    if(grid[i][j] == '0') {
        return ;
    }
    if(i - 1 >= 0 && sign[i - 1][j] == 0) {
        BFS(grid, i - 1, j, m, n);
    }
    if(i + 1 < m && sign[i + 1][j] == 0) {
        BFS(grid, i + 1, j, m, n);
    }
    if(j - 1 >= 0 && sign[i][j - 1] == 0) {
        BFS(grid, i, j - 1, m, n);
    }
    if(j + 1 < n && sign[i][j + 1] == 0) {
        BFS(grid, i, j + 1, m, n);
    }
    return ;
}

int numIslands(vector<vector<char>>& grid) {
    int ans = 0;
    int m = grid.size(),n = grid[0].size();
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == '1' && sign[i][j] == 0)
            {
                ans++;
                BFS(grid, i, j, m, n);
            }
        }
    }
    return ans;
}

int main()
{
    vector<vector<char>> grid = {{'1','1','1','1','0'},
                                  {'1','1','0','1','0'},
                                  {'1','1','0','0','0'},
                                  {'0','0','0','0','0'}};
    cout << numIslands(grid) << endl;
    return 0;
}