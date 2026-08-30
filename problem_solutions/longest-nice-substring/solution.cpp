#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int answer_l = -1, answer_r = -1; // left and right index of the substring, inclusive

    bool char_exists_in_both_cases(int l, int r, char c, const string &s){
        // substr takes (start_index, char_count)
        // char count from L to R inclusive = R - L + 1
        string substr = s.substr(l, r - l + 1);
        return substr.contains(toupper(c)) and substr.contains(tolower(c));
    }

    void solve(int l, int r, const string &s){
        if (l >= r) return;

        bool solvable = true;
        for (int i = l; i <= r; i++){
            char c = s[i];
            if (not char_exists_in_both_cases(l, r, c, s)){
                // char at i makes it not solvable
                solvable = false;
                // L ... i ... R
                // splitting around i

                // solve from L to i - 1
                solve(l, i - 1, s);
                // solve from i + 1 to R
                solve(i + 1, r, s);

                // must break since we already know this string cannot be 'nice'
                // and its two potentially nice parts have been solved by the two recursive calls
                break;
            }
        }

        if (solvable){
            if (answer_l == -1){ // if we have not found an answer before
                answer_l = l, answer_r = r;
            }
            else {
                // character count from L to R is R - L + 1
                int answer_len = answer_r - answer_l + 1;
                int current_len = r - l + 1;
                if (answer_len < current_len // found a longer nice string
                    or
                    answer_len == current_len and l < answer_l) // same length but earlier
                     answer_l = l, answer_r = r; // update the answer
            }
        }
    }

    string longestNiceSubstring(string s) {
        solve(0, size(s) - 1, s);

        return answer_l == -1 ? "" : s.substr(answer_l, answer_r - answer_l + 1);
    }
};

int main() {
    Solution sol;
    string s = "YazaAay";
    cout << sol.longestNiceSubstring(s) << endl;

    return 0;
}
