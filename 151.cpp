#include <iostream>
#include <string>

using namespace std;

string reverseWords(string s) {
    int n = s.size(),sign = 0,i;
    string ans,med;
    for(i = n - 1;i >= 0;-- i)
    {
        if(s[i] != ' ')
        {
            break;
        }
    }
    for(;i >= 0;-- i)
    {
        if(sign == 1 && s[i] != ' ')
        {
            ans += " " + med;
            med = "";
        }
        if(s[i] != ' ')
        {
            med.insert(0,1,s[i]);
            sign = 0;
        }
        else
        {
            sign = 1;
        }
    }
    ans += " " + med;
    ans.erase(0,1);
    return ans;
}

int main()
{
    string s = "  hello world  ";
    cout << reverseWords(s) << endl;
    return 0;
}