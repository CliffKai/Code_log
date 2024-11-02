#include<iostream>
#include<vector>

using namespace std;

int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int k) {
    int n = customers.size(),pre = 0,check = 0,sum = 0;
    for(int i = 0;i < k;++ i)
    {
        if(grumpy[i] == 1)
        {
            pre += customers[i];
        }
    }
    sum = pre;
    for(int i = k;i < n;++ i)
    {
        if(grumpy[i - k] == 1)
        {
            pre -= customers[i - k];
        }
        if(grumpy[i] == 1)
        {
            pre += customers[i];
        }
        if(pre > sum)
        {
            sum = pre;
            check = i - k + 1;
        }
    }
    sum = 0;
    for(int i = 0;i < n;++ i)
    {
        if(i >= check && i < check + k)
        {
            sum += customers[i];
        }
        else
        {
            if(grumpy[i] == 0)
            {
                sum += customers[i];
            }
        }
    }
    return sum;
}

int main()
{
    vector<int> customers = {1,0,1,2,1,1,7,5};
    vector<int> grumpy = {0,1,0,1,0,1,0,1};
    int k = 3;
    cout << maxSatisfied(customers,grumpy,k) << endl;
    return 0;
}