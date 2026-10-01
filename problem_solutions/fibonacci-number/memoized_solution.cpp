#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<int> memo;

    int helper(int k) {
        if (k == 0) return 0;
        if (k == 1) return 1;
        if (memo[k] != -1) return memo[k];

        memo[k] = helper(k - 1) + helper(k - 2);
        return memo[k];
    }

public:
    int fib(int n) {
        memo.assign(n + 2, -1);
        return helper(n);
    }
};

int main() {
    Solution sol;
    int n = 7;
    cout << sol.fib(n) << endl;

    return 0;
}
