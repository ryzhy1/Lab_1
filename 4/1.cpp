#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solve(int n, vector<pair<int, int> > segments) {
    sort(segments.begin(), segments.end(), [](const auto& x, const auto& y) {
        return x.second < y.second;
    });

    vector<int> points;
    int rightmost = -1;

    for (const auto& segment : segments) {
        if (segment.first > rightmost) {
            rightmost = segment.second;
            points.push_back(rightmost);
        }
    }

    return points;
}

int main() {
    int n;
    cin >> n;

    vector<pair<int, int> > segments(n);

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        segments[i] = make_pair(a, b);
    }

    vector<int> res = solve(n, segments);

    cout << res.size() << "\n";
    for (int point : res) {
        cout << point << " ";
    }
    cout << "\n";

    return 0;
}
