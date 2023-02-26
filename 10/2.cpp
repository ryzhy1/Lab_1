#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct Apple {
    int a, b, id;
};

bool cmp(const Apple &a1, const Apple &a2) {
    return a1.a + a1.b < a2.a + a2.b;
}

int main() {
    int n, s;
    fin >> n >> s;

    vector<Apple> apples(n);
    for (int i = 0; i < n; i++) {
        fin >> apples[i].a >> apples[i].b;
        apples[i].id = i + 1;
    }

    sort(apples.begin(), apples.end(), cmp);

    vector<int> ans;
    int sum_a = 0;
    for (int i = 0; i < n; i++) {
        sum_a += apples[i].a;
        if (sum_a > s) {
            fout << "-1\n";
            return 0;
        }
        ans.push_back(apples[i].id);
        s += apples[i].b;
    }

    for (int i = 0; i < n; i++) {
        fout << ans[i] << " ";
    }
    fout << endl;

    return 0;
}
