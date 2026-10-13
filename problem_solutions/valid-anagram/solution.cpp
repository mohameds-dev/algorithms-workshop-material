#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        vector<int> counts(26, 0);
        for (size_t i = 0; i < s.length(); i++) {
            counts[s[i] - 'a']++;
            counts[t[i] - 'a']--;
        }

        for (int count : counts) {
            if (count != 0) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution sol;
    cout << boolalpha;
    cout << sol.isAnagram("anagram", "nagaram") << endl; // true
    cout << sol.isAnagram("rat", "car") << endl;         // false
    return 0;
}
