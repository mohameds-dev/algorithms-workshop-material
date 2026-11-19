#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
private:
    void backtrack(
        int n,
        int open_count,
        int close_count,
        string &current,
        vector<string> &result
    ) {
        if (current.length() == 2 * n) {
            result.push_back(current);
            return;
        }

        if (open_count < n) {
            current.push_back('(');
            backtrack(n, open_count + 1, close_count, current, result);
            current.pop_back();
        }

        if (close_count < open_count) {
            current.push_back(')');
            backtrack(n, open_count, close_count + 1, current, result);
            current.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current;
        backtrack(n, 0, 0, current, result);
        return result;
    }
};

void test_solution() {
    Solution sol;
    vector<string> res1 = sol.generateParenthesis(1);
    assert(res1 == vector<string>{"()"});

    vector<string> res3 = sol.generateParenthesis(3);
    unordered_set<string> actual(res3.begin(), res3.end());
    unordered_set<string> expected = {"((()))", "(()())", "(())()", "()(())", "()()()"};
    assert(actual == expected);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
