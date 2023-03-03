#include <iostream>
#include <fstream>
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
    
    int n;
    fin >> n;

    vector<int> a(n);
    int sum = 0;

    for (int i = 0; i < n; i++) {
        fin >> a[i];
        sum += a[i];
    }

    if (sum % 2 != 0) {
        fout << -1 << endl;
        return 0;
    }

    vector<vector<int> > dp(n + 1, vector<int>(sum / 2 + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum / 2; j++) {
            if (j < a[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - a[i - 1]] + a[i - 1]);
            }
        }
    }

    if (dp[n][sum / 2] != sum / 2) {
        fout << -1 << endl;
        return 0;
    }

    vector<int> ans;
    int i = n, j = sum / 2;

    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i - 1][j]) {
            i--;
        } else {
            ans.push_back(i);
            j -= a[i - 1];
            i--;
        }
    }

    fout << ans.size() << endl;

    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i] << " ";
    }

    fout << endl;

    printTimeUse();
    printMemoryUsage();

    return 0;
}
