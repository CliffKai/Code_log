const int mx = 31622;
int pi[mx + 1];

auto init = [] {
    for(int i = 2; i <= mx; i++) {
        if(pi[i] == 0) {
            pi[i] = pi[i - 1] + 1;
            for(int j = i * i; j <= mx; j += i) {
                pi[j] = -1;
            }
        } else {
            pi[i] = pi[i - 1];
        }
    }
    return 0;
}();

class Solution {
public:
    int nonSpecialCount(int l, int r) {
        return r - l + 1 - (pi[(int)sqrt(r)] - pi[(int)sqrt(l - 1)]);
    }
};