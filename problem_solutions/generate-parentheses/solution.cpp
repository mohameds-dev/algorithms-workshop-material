#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void backtrack(int n, int openCount, int closeCount, string &current, vector<string> &result) {
        if ((int)current.length() == 2 * n) {
            result.push_back(current);
            return;
        }

        if (openCount < n) {
            current.push_back('(');
            backtrack(n, openCount + 1, closeCount, current, result);
            current.pop_back();
        }

        if (closeCount < openCount) {
            current.push_back(')');
            backtrack(n, openCount, closeCount + 1, current, result);
            current.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current;
        backtrack(n, 0, 0, current, result);
        return result;
    }
};

int main() {
    Solution sol;
    for (int n = 1; n <= 3; n++) {
        cout << "n = " << n << ": [";
        vector<string> result = sol.generateParenthesis(n);
        for (size_t i = 0; i < result.size(); i++) {
            cout << "\"" << result[i] << "\"";
            if (i + 1 < result.size()) cout << ", ";
        }
        cout << "]\n";
    }
    return 0;
}
