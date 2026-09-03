#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool both_cases_exist(char c, const string &s){
        return s.contains(toupper(c)) and s.contains(tolower(c));
    }

    int first_single_case_char(const string &s){
        for (int i = 0; i < (int)s.size(); i++){
            if (not both_cases_exist(s[i], s)) return i;
        }
        return -1;
    }

    pair<string, string> split_around_index(const string &s, int i){
        return {s.substr(0, i), s.substr(i + 1)};
    }

    string longest_nice_substring(const string &s){
        int i = first_single_case_char(s);
        if (i == -1) return s;

        auto [left, right] = split_around_index(s, i);
        string left_result = longest_nice_substring(left);
        string right_result = longest_nice_substring(right);
        return left_result.size() >= right_result.size() ? left_result : right_result;
    }

    string longestNiceSubstring(string s) {
        return longest_nice_substring(s);
    }
};

int main() {
    Solution sol;
    string s = "YazaAay";
    cout << sol.longestNiceSubstring(s) << endl;

    return 0;
}
