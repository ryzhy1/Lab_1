#include <iostream>
#include <fstream>

using namespace std;

// int solver(int n, int W, int dp[]) {
//     for (int i)
// }

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    int W, n;
    fin >> W >> n;

    int n = 5;
    int m = 4; 

    // создание двумерного динамического массива
    int **arr = new int*[n]; // выделяем память под указатели на строки
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m]; // выделяем память под каждую строку
    }

    // инициализация массива
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = i * j;
        }
    }

    // вывод массива
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    // освобождение памяти
    for (int i = 0; i < n; i++) {
        delete[] arr[i]; // освобождаем память, выделенную для каждой строки
    }
    delete[] arr; // освобождаем память, выделенную для указателей на строки

    for (int i = 0; i < n; i++) {

    }
}