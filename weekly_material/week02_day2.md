# Week 02, Day 2 (September 3, 2026)

## Today

Last time, we worked out the idea and proof behind Longest Nice Substring, then jumped straight
to the full recursive solution. Today we're building that same solution again, but this time
one small function at a time. Each function below is a self-contained task with its own hints
and a starting snippet in Python and C++. Later functions reuse the ones before them, so build
them in order.

By the end, you'll have all the pieces you need to solve
[LeetCode 1763, Longest Nice Substring](https://leetcode.com/problems/longest-nice-substring/description/)
yourself, start to finish.

**Syntax you'll need: uppercase and lowercase**

- Python: `c.upper()` and `c.lower()` return the uppercase and lowercase version of a character
  (or a whole string), as a new string.
- C++: `toupper(c)` and `tolower(c)` (from `<cctype>`, already included by `<bits/stdc++.h>`)
  take a character and return an `int`, so cast back with `(char)toupper(c)` if you need a
  `char` instead of an `int`.

<details>
<summary>1. both_cases_exist: does a character appear in both cases?</summary>

Write a function that takes a character `c` and a string `s`, and returns whether both the
uppercase and lowercase version of `c` appear somewhere in `s`.

- Python: `def both_cases_exist(c: str, s: str) -> bool`
- C++: `bool both_cases_exist(char c, const string &s)`

<details>
<summary>Hints</summary>

1. You need two checks to both be true: does the uppercase version of `c` appear in `s`, and
   does the lowercase version of `c` appear in `s`? Use the syntax note above to get each case.
2. Python has a built-in "does this string contain this character" check: `'a' in s`.
3. C++ doesn't have `in`, but `s.find(c) != string::npos` asks the same question (`find` returns
   `string::npos` when it doesn't find anything). If your compiler is recent enough, `s.contains(c)`
   works too.

</details>

<details>
<summary>Starting snippet (Python)</summary>

```python
def both_cases_exist(c: str, s: str) -> bool:
    # TODO: return True if both the uppercase and lowercase versions of c appear in s
    pass


def test_both_cases_exist():
    print(f"both_cases_exist('a', 'YazaAay') --> {both_cases_exist('a', 'YazaAay')}")  # expect True
    print(f"both_cases_exist('z', 'YazaAay') --> {both_cases_exist('z', 'YazaAay')}")  # expect False
    print(f"both_cases_exist('Y', 'YazaAay') --> {both_cases_exist('Y', 'YazaAay')}")  # expect True


if __name__ == "__main__":
    test_both_cases_exist()
```

</details>

<details>
<summary>Starting snippet (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

bool both_cases_exist(char c, const string &s) {
    // TODO: return true if both the uppercase and lowercase versions of c appear in s
}

void test_both_cases_exist() {
    cout << "both_cases_exist('a', \"YazaAay\") --> " << both_cases_exist('a', "YazaAay") << endl; // expect 1
    cout << "both_cases_exist('z', \"YazaAay\") --> " << both_cases_exist('z', "YazaAay") << endl; // expect 0
    cout << "both_cases_exist('Y', \"YazaAay\") --> " << both_cases_exist('Y', "YazaAay") << endl; // expect 1
}

int main() {
    test_both_cases_exist();
    return 0;
}
```

</details>

</details>

<details>
<summary>2. first_single_case_char: where does the string first break?</summary>

Write a function that scans a string `s` and returns the index of the first character that does
*not* appear in both cases. If every character passes, return `-1`, that's the signal that `s`
is already nice.

- Python: `def first_single_case_char(s: str) -> int`
- C++: `int first_single_case_char(const string &s)`

<details>
<summary>Hints</summary>

1. You already have a function that checks one character, you can reuse `both_cases_exist()` you
   wrote above.
2. Iterate over the string while tracking the index: `for i, c in enumerate(s)` in Python,
   `for (int i = 0; i < s.size(); i++)` in C++.
3. As soon as you find a character that fails the check, you have your answer, return it right
   away.
4. What should you return if the loop finishes and every character passed? That's what tells the
   caller "this string is already nice."

</details>

<details>
<summary>Starting snippet (Python)</summary>

```python
def first_single_case_char(s: str) -> int:
    # TODO: return the index of the first character where both_cases_exist(s[i], s) is False,
    # or -1 if every character passes
    pass


def test_first_single_case_char():
    print(f"first_single_case_char('YazaAay') --> {first_single_case_char('YazaAay')}")  # expect 2
    print(f"first_single_case_char('abc') --> {first_single_case_char('abc')}")  # expect 0
    print(f"first_single_case_char('abAB') --> {first_single_case_char('abAB')}")  # expect -1


if __name__ == "__main__":
    test_first_single_case_char()
```

</details>

<details>
<summary>Starting snippet (C++)</summary>

```cpp
int first_single_case_char(const string &s) {
    // TODO: return the index of the first character where both_cases_exist(s[i], s) is false,
    // or -1 if every character passes
}

void test_first_single_case_char() {
    cout << "first_single_case_char(\"YazaAay\") --> " << first_single_case_char("YazaAay") << endl; // expect 2
    cout << "first_single_case_char(\"abc\") --> " << first_single_case_char("abc") << endl; // expect 0
    cout << "first_single_case_char(\"abAB\") --> " << first_single_case_char("abAB") << endl; // expect -1
}
```

</details>

</details>

<details>
<summary>3. split_around_index: splitting the string around that character</summary>

Write a function that takes a string `s` and an index `i`, and returns the two pieces of `s` on
either side of index `i`: everything before `i`, and everything after `i`. The character at `i`
itself shouldn't appear in either piece, it's the one that broke niceness.

Later, `i` will come from `first_single_case_char()`, but for now just write this function
generically, for any index you're given.

- Python: `def split_around_index(s: str, i: int) -> tuple[str, str]`
- C++: `pair<string, string> split_around_index(const string &s, int i)`

<details>
<summary>Hints</summary>

1. Python slicing, `s[start:end]`, grabs everything from `start` up to (not including) `end`.
   What slice gets you everything before index `i`? Everything after it?
2. C++'s `s.substr(start, length)` takes a starting index and a length, not an end index. What
   length gets you from `i + 1` to the end of the string? (Hint: `s.size() - i - 1`.)
3. `s.substr(start)`, with no length argument, means "to the end of the string," in both C++ and
   as `s[start:]` in Python.

</details>

<details>
<summary>Starting snippet (Python)</summary>

```python
def split_around_index(s: str, i: int) -> tuple[str, str]:
    # TODO: return (left, right), the pieces of s before and after index i, excluding s[i]
    pass


def test_split_around_index():
    print(f"split_around_index('YazaAay', 2) --> {split_around_index('YazaAay', 2)}")  # expect ('Ya', 'aAay')
    print(f"split_around_index('abc', 0) --> {split_around_index('abc', 0)}")  # expect ('', 'bc')


if __name__ == "__main__":
    test_split_around_index()
```

</details>

<details>
<summary>Starting snippet (C++)</summary>

```cpp
pair<string, string> split_around_index(const string &s, int i) {
    // TODO: return {left, right}, the pieces of s before and after index i, excluding s[i]
}

void test_split_around_index() {
    auto [left, right] = split_around_index("YazaAay", 2);
    cout << "split_around_index(\"YazaAay\", 2) --> (" << left << ", " << right << ")" << endl; // expect (Ya, aAay)
}
```

</details>

</details>

<details>
<summary>4. longest_nice_substring: putting it all together</summary>

Now write the full recursive function, using the two functions you just built.

- Python: `def longest_nice_substring(s: str) -> str`
- C++: `string longest_nice_substring(const string &s)`

<details>
<summary>Hints</summary>

1. You've already built the two pieces you need: `first_single_case_char()` finds where the
   string breaks, `split_around_index()` splits it there. This function's job is to wire them
   together with recursion.
2. What should happen when `first_single_case_char(s)` returns `-1`? Look back at what that
   return value means, that's your base case.
3. Otherwise, split around that index, recursively call `longest_nice_substring()` on both
   pieces, then keep the longer result (prefer the left one on a tie).
4. This is the same idea from last session, now expressed with the small pieces you just wrote
   instead of all in one function.

</details>

<details>
<summary>Starting snippet (Python)</summary>

```python
def longest_nice_substring(s: str) -> str:
    # TODO: use first_single_case_char and split_around_index to recursively find and return
    # the longest nice substring of s
    pass


def test_longest_nice_substring():
    print(f"longest_nice_substring('YazaAay') --> {longest_nice_substring('YazaAay')}")  # expect 'aAa'
    print(f"longest_nice_substring('abc') --> {longest_nice_substring('abc')}")  # expect ''
    print(f"longest_nice_substring('abAB') --> {longest_nice_substring('abAB')}")  # expect 'abAB'


if __name__ == "__main__":
    test_longest_nice_substring()
```

</details>

<details>
<summary>Starting snippet (C++)</summary>

```cpp
string longest_nice_substring(const string &s) {
    // TODO: use first_single_case_char and split_around_index to recursively find and return
    // the longest nice substring of s
}

void test_longest_nice_substring() {
    cout << "longest_nice_substring(\"YazaAay\") --> " << longest_nice_substring("YazaAay") << endl; // expect aAa
    cout << "longest_nice_substring(\"abc\") --> " << longest_nice_substring("abc") << endl; // expect (empty)
    cout << "longest_nice_substring(\"abAB\") --> " << longest_nice_substring("abAB") << endl; // expect abAB
}
```

</details>

</details>

<details>
<summary>5. Solve it on LeetCode</summary>

Open [LeetCode 1763, Longest Nice Substring](https://leetcode.com/problems/longest-nice-substring/description/).
Wire your `longest_nice_substring()` into the `longestNiceSubstring` method LeetCode asks for
(call it directly, or fold its body in), and submit.

Once you've solved it, compare against the fully worked solution, built from these same four
functions:
[`misc_references/longest-nice-substring.cpp`](../misc_references/longest-nice-substring.cpp),
[`misc_references/longest-nice-substring.py`](../misc_references/longest-nice-substring.py).

</details>

<details>
<summary>6. Recap</summary>

- Every function above does one job, and has its own test cases you can run on its own, without
  needing the rest of the solution to exist yet.
- `longest_nice_substring()` barely does any work itself, it just calls the two functions before
  it and decides which half to keep. That's the payoff of building the small pieces first.
- This is the same divide and conquer idea, and the same proof, from last session: the
  implementation is just spread across four small functions instead of one.

</details>
