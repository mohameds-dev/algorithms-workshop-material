#include <bits/stdc++.h>
#include <cassert>
#include <sstream>
using namespace std;

void move_disk(int disk, char from_pole, char to_pole) {
    cout << "move disk " << disk << " from " << from_pole << " to " << to_pole << endl;
}

void hanoi(int n, char from_pole, char to_pole, char aux_pole) {
    if (n == 0) return;

    hanoi(n - 1, from_pole, aux_pole, to_pole);
    move_disk(n, from_pole, to_pole);
    hanoi(n - 1, aux_pole, to_pole, from_pole);
}

void test_solution() {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    hanoi(2, 'A', 'C', 'B');
    cout.rdbuf(old);

    string expected = "move disk 1 from A to B\nmove disk 2 from A to C\nmove disk 1 from B to C\n";
    assert(buffer.str() == expected);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
