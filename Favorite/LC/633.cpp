#include <iostream>

using namespace std;

//方法1：枚举
// bool judgeSquareSum(int c) {
//     for(long long  a = 0;a <= sqrt(c / 2);++ a)
//     {
//         long long b = sqrt(c - a * a);
//         if(c == a * a + b * b)
//         {
//             return true;
//         }
//     }
//     return false;
// }

//方法2：双指针
bool judgeSquareSum(int c) {
    long long a = 0,b = sqrt(c);
    while(a <= b)
    {
        if(a * a + b * b == c)
        {
            return true;
        }
        if(a * a + b * b > c)
        {
            -- b;
        }
        else
        {
            ++ a;
        }
    }
    return false;
}

int main()
{
    int c = 5;
    cout << judgeSquareSum(c) << endl;
    return 0;
}