#include<iostream>
#include<vector>

using namespace std;

//方法1：递归
void insert(vector<string> & ans,string med,int n)
{
    if(med.size() == n)
    {
        ans.push_back(med);
    }
    else
    {
        if(med[med.size() - 1] == '1')
        {
            insert(ans,med + "1",n);
            insert(ans,med + "0",n);
        }
        else
        {
            insert(ans,med + "1",n);
        }
    }
}

vector<string> validStrings(int n) {
    vector<string> ans;
    string med;
    insert(ans,med + "1",n);
    insert(ans,med + "0",n);
    return ans;
}

int main()
{
    int n;
    cin >> n;
    vector<string> ans = validStrings(n);
    for(auto & i : ans)
    {
        cout << i << endl;
    }
    return 0;
}
