/*
1. 最长回文子串 
给你一个字符串 s，找到 s 中最长的回文子串。
示例 1：
输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
示例 2：
输入：s = "cbbd"
输出："bb"
OJ:https://leetcode.cn/problems/longest-palindromic-substring/description/
*/

#include <iostream>

using namespace std;

// 方法1:中心扩展法
pair<int,int> fun(const string & s,int l,int r)
{
    while(l >= 0 && r < s.size() && s[l] == s[r])
    {
        -- l;
        ++ r;
    }
    return {l + 1,r - 1};
}

string longestPalindrome(string s) {
    int str = 0,end = 0;
    for(int i = 0;i < s.size();++ i)
    {
        auto [l1,r1] = fun(s,i,i);
        auto [l2,r2] = fun(s,i,i + 1);
        if(r1 - l1 > end -str)
        {
            str = l1;
            end = r1;
        }
        if(r2 - l2 > end -str)
        {
            str = l2;
            end = r2;
        }
    }
    return s.substr(str,end - str + 1);
}

int main()
{
    string s = "babad";
    cout << longestPalindrome(s) << endl;
    return 0;
}