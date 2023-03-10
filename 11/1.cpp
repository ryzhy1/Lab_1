#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <vector>

// ---------- macos ----------

#include <mach/task.h>
#include <mach/mach_init.h>

using namespace std;

void printMemoryUsage() { 
	struct task_basic_info t_info;
	mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

	if (KERN_SUCCESS != task_info(mach_task_self(),
		TASK_BASIC_INFO, (task_info_t)&t_info,
		&t_info_count))
	{
		printf("Error!");
	}
	else
	{
		printf("Memory used: %f MB\n", t_info.resident_size / 1024.0 / 1024.0);
	}
}

// ---------- windows ----------

// #include "windows.h"
// #include "psapi.h"

// using namespace std; 

// void printMemoryUsage() {
// 	PROCESS_MEMORY_COUNTERS_EX pmc;
// 	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
// 	SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

// 	cout << fixed << setprecision(6);
// 	cout << "Memory used: " << double(virtualMemUsedByMe) / (1024. * 1024) << " MB\n";
// }

// ---------- linux ----------

// #include <sys/resource.h>
// #include <sys/time.h>

// void printMemoryUsage() {
//    struct rusage usage;
// 	  getrusage(RUSAGE_SELF, &usage);
// 	  cout << "Memory used: " << usage.ru_maxrss / 1024.0 / 1024.0 << " MB\n";
// }

ifstream fin("input.txt"); 
ofstream fout("output.txt"); 

clock_t start;

void getFirstTime() {
	start = clock();
}

void printTimeUse() {
	printf("Time taken: %.7fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);
}

int main() {
    getFirstTime();
    
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
                dp[i][j] = max(dp[i-1][j-w[i-1]] + w[i-1], dp[i-1][j]);
            }
        }
        cout << endl;
    }

    fout << dp[n][W] << endl;

    for (int i = 0; i <= n; i++) {
        delete[] dp[i];
    }
    delete[] dp;

    printTimeUse();
    printMemoryUsage();

    return 0;
}