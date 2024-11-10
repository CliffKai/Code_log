#include<iostream>
#include<vector>

using namespace std;

vector<int> dailyTemperatures(vector<int>& t) {
    stack<int> s;
    int n = t.size();
    vector<int> ans(n);
    for(int i = 0;i < n;++ i)
    {
        while(!s.empty() && t[i] > t[s.top()])
        {
            ans[s.top()] = i - s.top();
            s.pop();
        }
        s.push(i);
    }
    return ans;
}

int main()
{
    vector<int> t = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> ans = dailyTemperatures(t);
    for(auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}