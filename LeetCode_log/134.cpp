#include<iostream>

using namespace std;

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int n = gas.size(),pre_cost = 0,min_cost = 0,ans = 0;
    for(int i = 0;i < n;++ i)
    {
        pre_cost += gas[i] - cost[i];
        if(pre_cost < min_cost)
        {
            min_cost = pre_cost;
            ans = i + 1;
        }
    }
    return pre_cost < 0 ? -1 : ans;
}

int main()
{
    vector<int> gas = {1,2,3,4,5},cost = {3,4,5,1,2};
    cout << canCompleteCircuit(gas,cost) << endl;

    return 0;
}