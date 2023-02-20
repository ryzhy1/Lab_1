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

void writer(int n, int p[]) {
    for (int i = 0; i < n; i++) {
        p[i] = generator(-10000, 10000);
        fout << p[i] << " ";
    }
    fout << endl;
}

int maxGen() {
    int n = 1000;
    fout << n << endl;
    int* p = new int[n];
    int* d = new int[n];
    writer(n, p);
    writer(n, d);
}

int main() {
    maxGen();
    return 0;
}