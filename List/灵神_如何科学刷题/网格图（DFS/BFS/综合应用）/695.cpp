#include <iostream>
#include <vector>

using namespace std;

int sign[301][301] = {0};
int BFS(vector<vector<int>>& grid, int i, int j, int m, int n) {
    sign[i][j] = 1;
    if(grid[i][j] == 0) {
        return 0;
    }
    int med = 1;
    if(i - 1 >= 0 && sign[i - 1][j] == 0) {
        med += BFS(grid, i - 1, j, m, n);
    }
    if(i + 1 < m && sign[i + 1][j] == 0) {
        med += BFS(grid, i + 1, j, m, n);
    }
    if(j - 1 >= 0 && sign[i][j - 1] == 0) {
        med += BFS(grid, i, j - 1, m, n);
    }
    if(j + 1 < n && sign[i][j + 1] == 0) {
        med += BFS(grid, i, j + 1, m, n);
    }
    return med;
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int ans = 0, med;
    int m = grid.size(),n = grid[0].size();
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == 1 && sign[i][j] == 0)
            {
                med = BFS(grid, i, j, m, n);
                ans = max(med, ans);
            }
        }
    }
    return ans;
}

int main() {
    vector<vector<int>> grid = {{1,1,0,0,0},
                                 {1,1,0,0,0},
                                 {0,0,0,1,1},
                                 {0,0,0,1,1}};
    cout << maxAreaOfIsland(grid) << endl;
    return 0;
}