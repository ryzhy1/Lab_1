#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sys/time.h>

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

int main() {
    getFirstTime();

    int n;
    fin >> n;

    vector<int> a(n);
    vector<int> b(n);

    for (int i = 0; i < n; i++) {
        int ai;
        fin >> ai;
        a[i] = ai;
    }
    for (int i = 0; i < n; i++) {
        int bi;
        fin >> bi;
        b[i] = bi;
    }

    sort(a.begin(), a.end(), greater<int>());
    sort(b.begin(), b.end(), greater<int>());

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    fout << sum << endl;
    printTimeUse();
    printMemoryUsage();
    return 0;
}