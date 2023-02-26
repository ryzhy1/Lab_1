#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <math.h>

// ---------- macos ----------

// #include <mach/task.h>
// #include <mach/mach_init.h>

// void printMemoryUsage() { 
// 	struct task_basic_info t_info;
// 	mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

// 	if (KERN_SUCCESS != task_info(mach_task_self(),
// 		TASK_BASIC_INFO, (task_info_t)&t_info,
// 		&t_info_count))
// 	{
// 		printf("Error!");
// 	}
// 	else
// 	{
// 		printf("Memory used: %f MB\n", t_info.resident_size / 1024.0 / 1024.0);
// 	}
// }

// ---------- windows ----------

#include "windows.h"
#include "psapi.h"

using namespace std;

void printMemoryUsage() {
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

	cout << fixed << setprecision(6);
	cout << "Memory used: " << double(virtualMemUsedByMe) / (1024. * 1024) << " MB\n";
}

// ---------- linux ----------

// #include <sys/resource.h>
// #include <sys/time.h>

// void printMemoryUsage() {
//    struct rusage usage;
// 	  getrusage(RUSAGE_SELF, &usage);
// 	  cout << "Memory used: " << usage.ru_maxrss / 1024.0 << " MB\n";
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

// ---------- code ----------

int phone(int n) {
    vector<vector<long long> > dp(10, vector<long long>(n + 1));
    int mod = pow(10, 9);
    for (int i = 0; i < 10; i++) {
        dp[i][1] = 1;
    }
    for (int j = 2; j <= n; j++) {
        for (int i = 0; i < 10; i++) {
            switch (i) {
                case 0:
                    dp[0][j] = (dp[4][j - 1] + dp[6][j - 1]) % mod;
                    break;
                case 1:
                    dp[1][j] = (dp[6][j - 1] + dp[8][j - 1]) % mod;
                    break;
                case 2:
                    dp[2][j] = (dp[9][j - 1] + dp[7][j - 1]) % mod;
                    break;
                case 3:
                    dp[3][j] = (dp[8][j - 1] + dp[4][j - 1]) % mod;
                    break;
                case 4:
                    dp[4][j] = (dp[0][j - 1] + dp[3][j - 1] + dp[9][j - 1]) % mod;
                    break;
                case 6:
                    dp[6][j] = (dp[0][j - 1] + dp[1][j - 1] + dp[7][j - 1]) % mod;
                    break;
                case 7:
                    dp[7][j] = (dp[6][j - 1] + dp[2][j - 1]) % mod;
                    break;
                case 8:
                    dp[8][j] = (dp[1][j - 1] + dp[3][j - 1]) % mod;
                    break;
                case 9:
                    dp[9][j] = (dp[2][j - 1] + dp[4][j - 1]) % mod;
                    break;
            }
        }
    }

   int sum = 0;

    for (int i = 1; i < 10; i++) {
        if (i != 8 && i != 0) {
            sum = (sum + dp[i][n]) % mod;
        }
    }
    return sum;
}

int main() {
    getFirstTime();

    int n;
    fin >> n;
    fout << phone(n) << endl;
    printTimeUse();
    printMemoryUsage();
    return 0;
}
