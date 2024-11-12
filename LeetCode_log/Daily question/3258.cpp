#include<iostream>
#include<vector>

using namespace std;

int countKConstraintSubstrings(string s, int k) {
    int ans = 0,sum[2]{},l = 0;
    for(int i = 0;i < s.length();++ i)
    {
        ++ sum[s[i] & 1];
        while(sum[0] > k && sum[1] > k)
        {
            -- sum[s[l++] & 1];
        }
        ans += i - l + 1;
    }
    return ans;
}

int main()
{
    string s = "101011";
    int k = 2;
    cout << countKConstraintSubstrings(s,k) << endl;
    return 0;
}