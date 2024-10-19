#include <iostream>
#include <vector>

using namespace std;

int lengthOfLastWord(string s) {
    int n = s.size();
    int ans = 0;
    while(n > 0 && (s[n] != ' ' || ans == 0))
    {
        -- n;
        if(s[n] == ' ')
        {
            continue;
        }
        ++ ans;
    }
    return ans;
}

int main()
{
    string s = "A";
    cout << lengthOfLastWord(s) << endl;
    return 0;
}