#include <iostream>

using namespace std;

int minimumRecolors(string s, int k) {
    int n = s.size(),pre = 0,ans = 0;
    for(int i = 0;i < k;++ i)
    {
        if(s[i] == 'W')
        {
            ++ pre;
        }
    }
    ans = pre;
    for(int i = k;i < n;++ i)
    {
        if(s[i] == 'w')
        {
            ++ pre;
        }
        if(s[i - k] == 'W')
        {
            -- pre;
        }
        ans = min(pre,ans);
    }
    return ans;
}

int main() {
    string s = "WBWBBBW";
    int k = 3;
    cout << minimumRecolors(s, k) << endl;
    return 0;
}