#include <iostream>

using namespace std;

int worth(char x)
{
    switch(x)
    {
        case 'I':return 1;break;
        case 'V':return 5;break;
        case 'X':return 10;break;
        case 'L':return 50;break;
        case 'C':return 100;break;
        case 'D':return 500;break;
        case 'M':return 1000;break;
    }
    return 0;
}
int romanToInt(string s) {
    int n = s.size(),ans = 0,sign = 0,num = 0;
    int med = worth(s[n - 1]);
    num = med,sign = med;
    ans += num;
    for(int i = n - 2;i >= 0;++ i)
    {
        med = worth(s[i]);
        num = med;
        if(med >= sign)
        {
            ans += num;
        }
        else
        {
            ans -= num;
        }
        sign = med;
    }
    return ans;
}

int main()
{
    string s = "III";
    cout << romanToInt(s) << endl;
    return 0;
}