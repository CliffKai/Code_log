#include <iostream>
#include <vector>

using namespace std;

int sign[1005];
int find(int i)
{
    if(sign[i] == i)
    {
        return i;
    }
    else
    {
        return find(sign[i]);
    }
}

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    for(int i = 0;i < edges.size();++ i)
    {
        sign[i + 1] = i + 1;
    }
    for(auto & med:edges)
    {
        int k1 = find(med[0]);
        int k2 = find(med[1]);
        if(k1 == k2)
        {
            return med;
        }
        else
        {
            sign[k1] = k2;
        }
    }
    return {0,0};
}

int main()
{
    vector<vector<int>> edges = {{1,2},{2,3},{3,4},{1,4},{1,5}};
    vector<int> res = findRedundantConnection(edges);
    cout << res[0] << " " << res[1] << endl;
    return 0;
}