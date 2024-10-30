#include<iostream>

using namespace std;

const int N = 1005;

int f[N] = {0};
int v[N],w[N];

int main()
{
    int n,m;
    cin >> n >> m;
    for(int i = 1;i <= n;++ i)
    {
        cin >> v[i] >> w[i];
    }
    //方法2：一维数组
    for(int i = 1;i <= n;++ i)
    {
        for(int j = m;j >= v[i];-- j)
        {
            f[j] = max(f[j],f[j - v[i]] + w[i]);
        }
    }
    //方法1：二维数组
    // for(int i = 1;i <= n;++ i)
    // {
    //     for(int j = 1;j <= m;++ j)
    //     {
    //         if(j < v[i])
    //         {
    //             f[i][j] = f[i - 1][j];
    //         }
    //         else
    //         {
    //             f[i][j] = max(f[i - 1][j],f[i - 1][j - v[i]] + w[i]);
    //         }
    //     }
    // }
    // cout << f[n][m];
    cout << f[m];
    return 0;
}