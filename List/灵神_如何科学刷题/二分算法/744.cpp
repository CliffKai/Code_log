#include<iostream>
#include<vector>

using namespace std;

char nextGreatestLetter(vector<char>& letters, char target) {
    if(letters[0] > target)
    {
        return letters[0];
    }
    char ans = letters[0];
    int i = 1,n = letters.size();
    while(i < n && letters[i] <= target)
    {
        ++ i;
    }
    if(i == n)
    {
        return ans;
    }
    else
    {
        return letters[i];
    }        
}

int main()
{
    vector<char> letters = {'c','f','j'};
    char target = 'a';
    cout << nextGreatestLetter(letters, target) << endl;
    return 0;
}