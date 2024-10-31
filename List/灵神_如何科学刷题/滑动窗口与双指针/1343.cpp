#include <iostream>
#include <vector>

using namespace std;

int numOfSubarrays(vector<int>& arr, int k, int threshold) {
    int n = arr.size(),pre = 0,ans = 0;
    threshold *= k;
    for(int i = 0;i < k;++ i)
    {
        pre += arr[i];
    }
    if(pre >= threshold)
    {
        ++ ans;
    }
    for(int i = k;i < n;++ i)
    {
        pre -= arr[i - k];
        pre += arr[i];
        if(pre >= threshold)
        {
            ++ ans;
        }
    }
    return ans;
}

int main()
{
    
}