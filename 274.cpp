#include<iostream>
#include<vector>

using namespace std;

int main()
{
    vector<int> citations = {3,0,6,1,5};
    cout << hIndex(citations) << endl;
    return 0;
}

int hIndex(vector<int>& citations) 
{
    int n = citations.size();
    vector<int> count(n + 1);
    for(int i = 0;i < n;++ i)
    {
        count[min(n,citations[i])] ++ ;
    }
    int c = 0;
    for(int i = n; ;-- i)
    {
        if(count[i])
        {
            c += count[i];
        }
        if(c >= i)
        {
            return i;
        }
    }
}