#include<iostream>
#include<vector>

using namespace std;

int candy(vector<int>& ratings) {
    int n = ratings.size();
    int pre = 1,dec = 0,inc = 1,ans = 1;
    for(int i = 1;i < n;++ i)
    {
        if(ratings[i - 1] <= ratings[i])
        {
            dec = 0;
            pre = ratings[i - 1] == ratings[i] ? 1 : pre + 1;
            ans += pre;
            inc = pre;
        }
        else
        {
            ++ dec;
            if(dec == inc)
            {
                ++ dec;
            }
            ans += dec;
            pre = 1;
        }
    }

    return ans;
}

int main()
{
    vector<int> ratings = {1,0,2};
    cout << candy(ratings) << endl;
    return 0;
}