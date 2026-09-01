#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool char_exists_in_both_cases(char c, const string &s){
        return s.contains(toupper(c)) and s.contains(tolower(c));
    }

    string solve(const string &s){
        if (s.size() == 0) return "";
        // n = 6
        // 0 1 2 (3) 4 5
        // i = 3
        // start at 4 (i + 1), take n - 4 (n - i - 1)

        int n = s.size();
        for (int i = 0; i < n; i++){
            if (not char_exists_in_both_cases(s[i], s)){
                // splitting around i

                // solve from 0 to i - 1 --> start from index 0, and take i characters
                string left = solve(s.substr(0, i));
                // solve from i + 1 to end --> start from index i + 1, take n - i - 1 characters
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

int main() {
    Solution sol;
    string s = "YazaAay";
    cout << sol.longestNiceSubstring(s) << endl;

    return 0;
}
