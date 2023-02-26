#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>


// ---------- macos ----------

// #include <mach/task.h>
// #include <mach/mach_init.h>

// using namespace std;

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

// using namespace std;

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

int main() {
    getFirstTime();

    int minCost = pow(10, 10);
    int N;
    fin >> N;

    int result = 0;
    vector<int> prices(7);
    for (int i = 0; i < 7; i++) {
        fin >> prices[i];
    }

    for (int i = 6; i >= 0; i--) {
        int N2 = N;
        if (N != 0) {
            int k = N / pow(10, i);
            if (k > 0) {
                result += k * prices[i];
                N -= k * pow(10, i);
            } 
            if (k == 0) {
                N2 -= pow(10, i);
                if (N2 <= 0) {
                    minCost = min(minCost, prices[i]);
                }
            }
        } else {
            break;
        }
    }

    fout << min(result, minCost);

    fin.close();
    fout.close();
    printTimeUse();
    printMemoryUsage();
    return 0;
}
