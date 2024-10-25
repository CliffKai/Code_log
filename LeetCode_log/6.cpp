#include <iostream>
#include <string>

using namespace std;

string convert(string s, int numRows) {
    int n = s.size();
    if(numRows == 1 || numRows >= n)
    {
        return s;
    }
    string ans;
    for(int i = 0;i < numRows;++ i)
    {
        if(i == 0 || i == numRows - 1)
        {
            for(int j = i;j < n;j += (numRows - 1) * 2)
            {
                ans.push_back(s[j]);
            }
        }
        else
        {
            for(int j = i;j < n;j += (numRows - 1) * 2)
            {
                ans.push_back(s[j]);
                if((j + (numRows - 1) * 2 - i * 2) < n)
                {
                    ans.push_back(s[j + (numRows - 1) * 2 - i * 2]);
                }
            }
        }
    }
    return ans;
}

int main()
{
    string s = "PAYPALISHIRING";
    cout << convert(s,3) << endl;
    return 0;
}