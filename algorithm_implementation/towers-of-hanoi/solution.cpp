#include <bits/stdc++.h>
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

int main() {
    hanoi(3, 'A', 'C', 'B');

    return 0;
}
