#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int fib(int n) {
        // LeetCode constrains n to 0..30
        int fibVals[31];

        // equivalent to the base case in the recursive solution
        fibVals[0] = 0;
        fibVals[1] = 1;

        for (int i = 2; i <= n; ++i) {
            // transition
            fibVals[i] = fibVals[i - 1] + fibVals[i - 2];
        }

        return fibVals[n];
    }
};

int main() {
    Solution sol;
    int n = 7;
    cout << sol.fib(n) << endl;

    return 0;
}
