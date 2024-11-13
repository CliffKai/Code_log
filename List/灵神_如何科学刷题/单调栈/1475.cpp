#include <bits/stdc++.h>

using namespace std;

long long Mymap[1001][1001] = {0};

vector<int> finalPrices(vector<int>& prices) {
    int n = prices.size();
    vector<int> ans(n,0);
    stack<int> st;
    for(int i = 0;i < n;++ i)
    {
        while(!st.empty() && prices[i] <= prices[st.top()])
        {
            int k = st.top();
            st.pop();
            ans[k] = prices[k] - prices[i];
        }
        st.push(i);
    }
    while(!st.empty())
    {
        int k = st.top();
        st.pop();
        ans[k] = prices[k];
    }
    return ans;
}


int main()
{
    vector<int> prices = {10,1,1,6};
    vector<int> ans = finalPrices(prices);
    for(int i = 0;i < ans.size();++ i)
    {
        cout << ans[i] << " ";
    }
    return 0;
}