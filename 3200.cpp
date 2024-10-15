#include<iostream>

using namespace std;

int H(int a,int b)
{
    int ans = 0,ai = 1,bi = 2;
    while(a >= 0 && b >= 0)
    {
        a -= ai;
        if(a >= 0)
        {
            ++ ans;
            ai += 2;
        }
        else
        {
            break;
        }
        b -= bi;
        if(b >= 0)
        {
            ++ ans;
            bi += 2;
        }
        else
        {
            break;
        }
    }
    return ans;
}

int maxHeightOfTriangle(int red, int blue) {
    int a = H(red,blue),b = H(blue,red);
    return a > b ? a : b;
}

int main()
{
    cout << maxHeightOfTriangle(2,4) << endl;

    return 0;
}