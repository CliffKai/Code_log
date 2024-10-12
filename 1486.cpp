#include <iostream>

using namespace std;

int main()
{
    int n = 5, start = 0;
    cout << xorOperation(n, start) << endl;
    return 0;
}

int xor_n(int n)
{
    switch (n % 4)
    {
    case 0:
        return n;
    case 1:
        return 1;
    case 2:
        return n + 1;
    default:
        return 0;
    }
}

int xorOperation(int n, int start)
{
    int a = start / 2;
    int b = n & start & 1;
    return (xor_n(a + n - 1) ^ xor_n(a - 1)) * 2 + b;
}
