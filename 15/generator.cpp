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

char arr[6] = {'(', ')', '[', ']', '{', '}'};


int maxGen() {
    int n = 100;
    for (int i = 0; i < n; i++) {
        int v = generator(1, 10000);
        fout << arr[v % 6];
    }
}

int main() {
    maxGen();
    return 0;
}