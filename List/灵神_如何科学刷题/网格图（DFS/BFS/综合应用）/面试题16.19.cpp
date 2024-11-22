#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int sign[1001][1001] = {0};
int BFS(vector<vector<int>>& grid, int i, int j, int m, int n) {
    sign[i][j] = 1;
    if (grid[i][j] != 0) {
        return 0;
    }
    int med = 1;
    if (i - 1 >= 0 && sign[i - 1][j] == 0) {
        med += BFS(grid, i - 1, j, m, n);
    }
    if (i + 1 < m && sign[i + 1][j] == 0) {
        med += BFS(grid, i + 1, j, m, n);
    }
    if (j - 1 >= 0 && sign[i][j - 1] == 0) {
        med += BFS(grid, i, j - 1, m, n);
    }
    if (j + 1 < n && sign[i][j + 1] == 0) {
        med += BFS(grid, i, j + 1, m, n);
    }
    if (i - 1 >= 0 && j - 1 >= 0 && sign[i - 1][j - 1] == 0) {
        med += BFS(grid, i - 1, j - 1, m, n);
    }
    if (i - 1 >= 0 && j + 1 < n && sign[i - 1][j + 1] == 0) {
        med += BFS(grid, i - 1, j + 1, m, n);
    }
    if (i + 1 < m && j - 1 >= 0 && sign[i + 1][j - 1] == 0) {
        med += BFS(grid, i + 1, j - 1, m, n);
    }
    if (i + 1 < m && j + 1 < n && sign[i + 1][j + 1] == 0) {
        med += BFS(grid, i + 1, j + 1, m, n);
    }
    return med;
}

vector<int> pondSizes(vector<vector<int>>& land) {
    int med;
    vector<int> ans;
    int m = land.size(), n = land[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (land[i][j] == 0 && sign[i][j] == 0) {
                med = BFS(land, i, j, m, n);
                ans.push_back(med);
            }
        }
    }
    std::set<int> unique_ans(ans.begin(), ans.end());
    std::sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    vector<vector<int>> land = {{0, 2, 1, 0},
                                 {0, 1, 0, 1},
                                 {1, 1, 0, 1},
                                 {0, 1, 0, 1}};
    vector<int> ans = pondSizes(land);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}