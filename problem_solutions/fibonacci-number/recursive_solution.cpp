#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int fib(int n) {
        // base case
        if (n == 0) return 0;
        if (n == 1) return 1;

        // transition
        return fib(n - 1) + fib(n - 2);
    }
};

int main() {
    Solution sol;
    int n = 7;
    cout << sol.fib(n) << endl;

    return 0;
}
