#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");

    int n;
    input_file >> n;

    vector<int> a(n);
    int sum = 0;

    for (int i = 0; i < n; i++) {
        input_file >> a[i];
        sum += a[i];
    }

    if (sum % 3 != 0) {
        output_file << 0 << endl;
        return 0;
    }

    vector<vector<int>> dp(n + 1, vector<int>(sum / 3 + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum / 3; j++) {
            if (j < a[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - a[i - 1]] + a[i - 1]);
            }
            
        } 
    }
    

    if (dp[n][sum / 3] != sum / 3) {
        output_file << 0 << endl;
        return 0;
    }

    vector<int> ans;
    int i = n, j = sum / 3;

    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i - 1][j]) {
            i--;
        } else {
            ans.push_back(i);
            j -= a[i - 1];
            i--;
        }
    }

    output_file << 1;

    return 0;
}
