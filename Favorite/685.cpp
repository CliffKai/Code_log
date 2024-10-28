#include <iostream>
#include <vector>

using namespace std;

int fa[1001];
int n;
void init()
{
    for(int i = 1;i <= n;++ i)
    {
        fa[i] = i;
    }
}
int find(int i)
{
    if(i == fa[i])
    {
        return i;
    }
    else
    {
        fa[i] = find(fa[i]);
        return fa[i];
    }
}
void join(int i,int j)
{
    i = find(i);
    j = find(j);
    if(i == j)
    {
        return;
    }
    fa[j] = i;
}
bool judge(int i,int j)
{
    i = find(i);
    j = find(j);
    return i == j;
}
vector<int> getRemoveEdge(const vector<vector<int>> & edges)
{
    init();
    for(int i = 0;i < n;++ i)
    {
        if(judge(edges[i][0],edges[i][1]))
        {
            return edges[i];
        }
        join(edges[i][0],edges[i][1]);
    }
    return {0,0};
}
bool isTreeAfterRemoveEdge(const vector<vector<int>> & edges,int deleteEdge)
{
    init();
    for(int i = 0;i < n;++ i)
    {
        if(i == deleteEdge)
        {
            continue;
        }
        if(judge(edges[i][0],edges[i][1]))
        {
            return false;
        }
        join(edges[i][0],edges[i][1]);
    }
    return true;
}

vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
    int inDegree[1001] = {0};
    n = edges.size();
    for(int i = 0;i < n;++ i)
    {
        ++ inDegree[edges[i][1]];
    }
    vector<int> vec;
    for(int i = n - 1;i >= 0;-- i)
    {
        if(inDegree[edges[i][1]] == 2)
        {
            vec.push_back(i);
        }
    }
    if(vec.size() > 0)
    {
        if(isTreeAfterRemoveEdge(edges,vec[0]))
        {
            return edges[vec[0]];
        }
        else
        {
            return edges[vec[1]];
        }
    }
    return getRemoveEdge(edges);
}

int main()
{
    vector<vector<int>> edges = {{1,2},{1,3},{2,3}};
    vector<int> res = findRedundantDirectedConnection(edges);
    cout << res[0] << " " << res[1] << endl;
    return 0;
}
