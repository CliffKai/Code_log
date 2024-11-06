#include<iostream>
#include<vector>

using namespace std;

int maxScore(vector<int>& cardPoints, int k) {
    int n = cardPoints.size(),sign = 0,ans = 0,pre = 0,i;
    for(i = n - k;i < n;++ i)
    {
        pre += cardPoints[i];
    }
    ans = pre;
    for(int j = 0;j < k;++ j,++ i)
    {
        pre -= cardPoints[i - k];
        pre += cardPoints[j];
        ans = max(ans,pre);
    }
    return ans;
}

int main()
{
    vector<int> cardPoints = {1,2,3,4,5,6,1};
    int k = 3;
    cout << maxScore(cardPoints, k) << endl;
    return 0;
}