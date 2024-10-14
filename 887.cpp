#include<iostream>

using namespace std;

int main()
{
    cout << superEggDrop(2,6) << endl;
    cout << superEggDrop(3,14) << endl;
    return 0;
}

int dfs(int k,int t)
{
    if(k ==1||t == 1)
    {
        return t + 1;
    }
    return dfs(k - 1,t - 1) + dfs(k,t - 1);
}

int superEggDrop(int k, int n) {
    int t = 1;
    while(dfs(k,t) < n + 1)
    {
        ++ t;
    }
    return t;
}