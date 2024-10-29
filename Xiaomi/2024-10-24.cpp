/*
1. 复原 IP 地址
有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。
- 例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP 地址，这些地址可以通过在 s 中插入 '.' 来形成。你 不能 重新排序或删除 s 中的任何数字。你可以按 任何 顺序返回答案。
 
示例 1：
输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]
示例 2：
输入：s = "0000"
输出：["0.0.0.0"]
示例 3：
输入：s = "101023"
输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
OJ:https://leetcode-cn.com/problems/restore-ip-addresses/description/
*/
#include<iostream>
#include<vector>

using namespace std;

bool check(string str)
{
    if(str.size() > 1 && str[0] == '0')
    {
        return false;
    }
    if(str.size() > 3)
    {
        return false;
    }
    if(str.size() == 3)
    {
        if(str[0] > '2')
        {
            return false;
        }
        if(str[0] == '2')
        {
            if(str[1] > '5')
            {
                return false;
            }
            if(str[1] == '5')
            {
                if(str[2] > '5')
                {
                    return false;
                }
            }
        }
    }
    return true;
}

vector<string> restoreIpAddresses(string s) {
    string med1,med2,med3,med4;
    vector<string> ans;
    for(int i1 = 1;i1 < s.size() - 4;++ i1)
    {
        med1 = s.substr(0,i1 - 0);
        if(check(med1) == false)
        {
            continue;
        }
        for(int i2 = i1 + 1;i2 < s.size() - 3;++ i2)
        {
            med2 = s.substr(i1,i2 - i1);
            if(check(med2) == false)
            {
                continue;
            }
            for(int i3 = i2 + 1;i3 < s.size() - 2;++ i3)
            {
                med3 = s.substr(i2,i3 - i2);
                if(check(med3) == false)
                {
                    continue;
                }
                med4 = s.substr(i3,s.size() - i3);
                if(check(med4))
                {
                    ans.push_back(med1 + "." + med2 + "." + med3 + "." + med4);
                }
            }
        }
    }
    return ans;
}

int main()
{
    string s = "25525511135";
    vector<string> ans = restoreIpAddresses(s);
    for(auto & i : ans)
    {
        cout << i << endl;
    }
    return 0;
}
