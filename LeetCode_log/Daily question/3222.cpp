#include<iostream>

using namespace std;

string losingPlayer(int x, int y) {
    int i = x,j = y / 4,sign = 1;
    while(i-- != 0 && j-- != 0)
    {
        sign ^= 1;
    }
    if(sign)
    {
        return "Bob";
    }
    return "Alice";
}

int main()
{
    int x = 3,y = 5;
    cout << losingPlayer(x, y) << endl;
    return 0;
}