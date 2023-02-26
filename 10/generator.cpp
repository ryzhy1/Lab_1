#include <iostream>
#include <fstream>
#include <random>

using namespace std;

ofstream fout("input.txt");

int generator(int l, int r) {
    random_device a;
    mt19937 gen(a());
    uniform_int_distribution <> distrib(l, r);
    return distrib(gen);
}

int main() {
    int n = 1000, s = 1000;

    fout << n << " " << s << endl;

    for (int i = 0; i < n; i++) {
        fout << generator(1, 10000) << " " << generator(1, 10000) << endl;
    }
}