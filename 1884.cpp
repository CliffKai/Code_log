#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int n = 100;
    cout << twoEggDrop1(n) << endl;
    cout << twoEggDrop2(n) << endl;
    return 0;
}

//way 1
int twoEggDrop1(int n) {
    return (int)ceil(sqrt(n * 8 + 1)) / 2;
}

//way 2
int twoEggDrop2(int n) {
    int ans = 0;
    while(n > 0)
    {
        n -= ++ ans;
    }
    return ans;
}