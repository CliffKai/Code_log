#include<iostream>

using namespace std;

int minChanges(int n, int k) {
    //return (n & k) == k ? __builtin_popcount(n ^ k) : -1;
    if((n & k) == k)
    {
        return __builtin_popcount(n ^ k);
    }
    return -1;
}

int main()
{
    int n = 5,k = 3;
    cout << minChanges(n,k) << endl;
    return 0;
}