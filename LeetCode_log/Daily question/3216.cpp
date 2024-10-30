#include <iostream>

using namespace std;

string getSmallestString(string s) {
    int sign = s[0] % 2;
    for(int i = 1;i < s.size();++ i)
    {
        if(s[i - 1] > s[i] && sign == s[i] % 2)
        {
            swap(s[i - 1],s[i]);
            break;
        }
        sign = s[i] % 2;
    }
    return s;
}

int main() {
    string s = "45320";
    cout << getSmallestString(s) << endl;
    return 0;
}