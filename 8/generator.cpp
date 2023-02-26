#include <iostream>
#include <fstream>

using namespace std;

ofstream fin("input.txt");

int main() {
    fin << 1000 << endl;

    for (int i = 1; i < 2000; i++) {
        fin << i << " " << ++i << endl;
    }
}