#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Apple {
    int a, b, number;
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, s;
    cin >> n >> s;

    vector<Apple> plusa, minusb;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        if (b - a > 0)
            plusa.emplace_back(Apple{a, b, i});
        else
            minusb.emplace_back(Apple{a, b, i});
    }

    sort(begin(plusa), end(plusa), [](const Apple& a, const Apple& b) {
        return a.a < b.a;
    });
    sort(begin(minusb), end(minusb), [](const Apple& a, const Apple& b) {
        return a.b > b.b;
    });

    vector<int> ressequence;
    for (const auto& apple : plusa) {
        if (s - apple.a <= 0) {
            cout << -1 << endl;
            return 0;
        }
        s += apple.b - apple.a;
        ressequence.push_back(apple.number);
    }

    for (const auto& apple : minusb) {
        if (s - apple.a <= 0) {
            cout << -1 << endl;
            return 0;
        }
        s += apple.b - apple.a;
        ressequence.push_back(apple.number);
    }

    for (const auto& num : ressequence) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
