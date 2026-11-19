#include <cassert>
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string solve(const string &s){
        // one pass to remember every character in s, so the checks below cost O(1) each
        unordered_set<char> chars_in_s(s.begin(), s.end());

        int n = s.size();
        for (int i = 0; i < n; i++){
            if (not chars_in_s.count(toupper(s[i])) or not chars_in_s.count(tolower(s[i]))){
                string left = solve(s.substr(0, i));
                string right = solve(s.substr(i + 1, n - i - 1));

                return left.size() < right.size() ? right : left;
            }
        }

        return s;
    }

    string longestNiceSubstring(string s) {
        return solve(s);
    }
};

void test_solution() {
    Solution sol;
    assert(sol.longestNiceSubstring("YazaAay") == "aAa");
    assert(sol.longestNiceSubstring("Bb") == "Bb");
    assert(sol.longestNiceSubstring("c") == "");
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
