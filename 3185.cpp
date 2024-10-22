#include<iostream>
#include<vector>

using namespace std;

long long int countCompleteDayPairs(vector<int>& hours) {
    vector<long long int> hash(24,0);
    long long int n = hours.size(),ans = 0;
    for(int i = 0;i < n;++ i)
    {
        ++ hash[hours[i] % 24];
    }
    for(int i = 1;i < 12;++ i)
    {
        ans += hash[i] * (hash[24 - i]);
    }
    ans += (hash[0] * (hash[0] - 1)) / 2;
    ans += (hash[12] * (hash[12] - 1)) / 2;
    return ans;
}

int main()
{
    vector<int> hours = {9,9,9,9,9,9,9,9,9,9};
    cout << countCompleteDayPairs(hours) << endl;
    return 0;
}