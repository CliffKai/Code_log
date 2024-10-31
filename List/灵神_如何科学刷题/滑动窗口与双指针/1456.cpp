#include<iostream>

using namespace std;

int check(char a)
{
    if(a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u')
    {
        return 1;
    }
    return 0;
}

int maxVowels(string s, int k) {
    int n = s.size(),pre = 0,ans = 0;
    for(int i = 0;i < k;++ i)
    {
        pre += check(s[i]);
    }
    ans = pre;
    for(int i = k;i < n;++ i)
    {
        pre += check(s[i]);
        pre -= check(s[i - k]);
        ans = max(ans,pre);
    }
    return ans;
}

int main()
{
    string s = "abciiidef";
    int k = 3;
    cout << maxVowels(s,k) << endl;
    return 0;
}