#include<iostream>
#include<vector>

using namespace std;

vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
    vector<int> dp(n);
    vector<vector<int>> prev(n);
    for(int i = 1; i < n; i++) {
        dp[i] = i;
        prev[i].push_back(i - 1);
    }
    vector<int> ans(queries.size());
    int k = 0;
    for(auto & med : queries) {
        prev[med[1]].push_back(med[0]);
        for(int i = med[1]; i < n; i++) {
            for(auto & j : prev[i]) {
                dp[i] = min(dp[i],dp[j] + 1);
            }
        }
        ans[k++] = dp[n - 1];
    }
    return ans;
}

int main() {
    int n = 5;
    vector<vector<int>> queries = {{0,4},{4,2},{2,3},{4,1}};
    vector<int> ans = shortestDistanceAfterQueries(n,queries);
    for(auto & i : ans) {
        cout << i << " ";
    }
    return 0;
}