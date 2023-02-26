#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

// int solver(int n, int W, int dp[]) {
//     for (int i)
// }

ifstream fin("input.txt");
ofstream fout("output.txt");


int main() {
    int W, n;
    fin >> W >> n;

    // чтение весов слитков
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        fin >> w[i];
    }

    sort(w.begin(), w.end());

    // создание двумерного динамического массива
    int **dp = new int*[n];
    for (int i = 0; i <= n; i++) {
        dp[i] = new int[W];
    }

    // заполнение первой строки нулями
    for (int w = 0; w <= W; w++) {
        dp[0][w] = 0;
    }

    // заполнение таблицы
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            dp[i][j] = dp[i-1][j]; // заполняем из предыдущей строки
            if (w[i-1] <= j) { // если слиток помещается в рюкзак
                int val = dp[i-1][j-w[i-1]] + w[i-1]; // проверяем, увеличится ли суммарный вес
                if (dp[i][j] < val) { // если увеличится, то записываем новое значение
                    dp[i][j] = val;
                }
            }
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    // вывод максимального веса золота
    fout << dp[n][W] << endl;

    // освобождение памяти
    for (int i = 0; i <= n; i++) {
        delete[] dp[i];
    }
    delete[] dp;

    return 0;
}