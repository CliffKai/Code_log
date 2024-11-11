#include<iostream>
#include<vector>
#include<algorithm>
#include <climits>

using namespace std;

int dfs(int i,int j,const vector<int>& cuts,vector<vector<int>>& memo)
{
    if(i + 1 == j)
    {
        return 0;
    }
    int& res = memo[i][j];
    if(res)
    {
        return res;
    }
    res = INT_MAX;
    for(int k = i + 1;k < j;++ k)
    {
        res = min(res,dfs(i,k,cuts,memo) + dfs(k,j,cuts,memo));
    }
    res += cuts[j] - cuts[i];

    return res;
}

int minCost(int n, vector<int>& cuts) {
    cuts.push_back(0);
    cuts.push_back(n);
    sort(cuts.begin(), cuts.end());

    int m = cuts.size();
    vector<vector<int>> memo(m, vector<int>(m));
    return dfs(0, m - 1, cuts, memo);
}

int main()
{
    int n = 7;
    vector<int> cuts = {1,3,4,5};
    cout << minCost(n,cuts) << endl;
    return 0;
}