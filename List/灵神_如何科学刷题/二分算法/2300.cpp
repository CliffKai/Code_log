#include<iostream>
#include<vector>

using namespace std;


int fun(long long int k1,long long int k2,vector<int> & potions,long long int str,long long int end)
{
    if(str == end)
    {
        return str;
    }
    if(k1 * potions[(str + end) / 2] < k2)
    {
        return fun(k1,k2,potions,(str + end) / 2 + 1,end);
    }
    else
    {
        return fun(k1,k2,potions,str,(str + end) / 2);
    }
}

vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
    ranges::sort(potions);
    long long int n = spells.size(),n2 = potions.size();
    vector<int> ans(n,0);
    for(long long int i = 0;i < n;++ i)
    {
        long long int j = fun(spells[i],success,potions,0,n2 - 1);
        if(j != n2 - 1)
        {
            ans[i] = n2 - j;
        }
        else
        {
            long long med = spells[i];
            med *= potions[n2 - 1];
            if(med < success)
            {
                ans[i] = 0;
            }
            else
            {
                ans[i] = n2 - j;
            }
        }
    }
    return ans;
}

int main()
{
    vector<int> spells = {1,2,3,4,5,6,7};
    vector<int> potions = {1,2,3,4,5,6,7};
    long long success = 7;
    vector<int> ans = successfulPairs(spells,potions,success);
    for(int i = 0;i < ans.size();++ i)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}