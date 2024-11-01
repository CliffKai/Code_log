#include<iostream>
#include<vector>

using namespace std;

long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
    int n = energyDrinkA.size();
    long long A = energyDrinkA[0],B = energyDrinkB[0],med = 0;
    for(int i = 1;i < n;++ i)
    {
        med = A;
        A = max(A + energyDrinkA[i],B);
        B = max(B + energyDrinkB[i],med);
    }
    return max(A,B);
}

int main()
{
    vector<int> energyDrinkA = {1,2,3,4,5};
    vector<int> energyDrinkB = {5,4,3,2,1};
    cout << maxEnergyBoost(energyDrinkA,energyDrinkB) << endl;
    return 0;
}