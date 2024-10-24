#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int findWinningPlayer(vector<int>& skills, int k) {
    int max_i = 0, win = 0;
    for (int i = 1; i < skills.size() && win < k; i++) {
        if (skills[i] > skills[max_i]) {
            max_i = i;
            win = 0;
        }
        win++;
    }
    return max_i;
}

int main() {
    vector<int> skills = {16,4,7,17};
    int k = 562084119;
    cout << findWinningPlayer(skills, k) << endl;
    system("pause");
    return 0;
}