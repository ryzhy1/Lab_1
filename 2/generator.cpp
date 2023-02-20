#include <iostream>
#include <fstream>
#include <time.h>
#include <random>

using namespace std;

ofstream fout("input.txt");

int generator(int l, int r) {
    random_device a;
    mt19937 gen(a());
    uniform_int_distribution <> distrib(l, r);
    return distrib(gen);
}

int maxGen() {
    int K = 10000;
    int m = 400;
    int n = 300;
    fout << K << endl << m << endl << n << endl;
    int* p = new int[n];
    for (int i = 0; i < n; i++) {
        p[i] = generator(1, 10000);
        fout << p[i] << " ";
    }
}

int main() {
    maxGen();
    return 0;
}