#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main()
{
    vector<int> nums1 = {1,2,3,4,5,6};
    vector<int> nums2 = {1,2,3,4,5,6};
    int k = 2;
    cout << numberOfPairs(nums1,nums2,k) << endl;
    return 0;
}
//同3162，只是3162可以暴力，3164不行
long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    unordered_map<int,int> hash;
    for(int num : nums2)
    {
        hash[num] ++ ;
    }
    long long ans = 0;
    for(int num : nums1)
    {
        if(num % k != 0)
        {
            continue;
        }
        int med = num / k;
        for(int i = 1;i * i <= med; ++ i)
        {
            if(med % i != 0)
            {
                continue;
            }
            ans += hash[i];
            if(i * i != med)
            {
                ans += hash[med / i];
            }
        }
    }
    return  ans;
}