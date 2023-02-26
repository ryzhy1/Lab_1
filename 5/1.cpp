#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

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

#include "Windows.h"
#include "psapi.h"
#include <iomanip>

using namespace std;

void printMemoryUsage()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

    cout << fixed << setprecision(6);
    cout << "Memory used: " << double(virtualMemUsedByMe) / (1024. * 1024) << " MB\n";
}

// // ---------- linux ----------

// // #include <sys/resource.h>
// // #include <sys/time.h>

// // void printMemoryUsage() {
// //    struct rusage usage;
// // 	  getrusage(RUSAGE_SELF, &usage);
// // 	  cout << "Memory used: " << usage.ru_maxrss / 1024.0 << " MB\n";
// // }


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

    vector<int> result;
    int current_sum = 0;

    if (current_sum != n) {
        for (int i = 1; ; i++) {
            if (current_sum + i <= n) {
                current_sum += i;
                result.push_back(i);
            } 
            else if (current_sum + i > n){
                result.back() += n - current_sum;
                break;
            }
        }
    }


    
    
    fout << result.size() << endl;

    for (auto x : result) {
        fout << x << " ";
    }

    printTimeUse();
    printMemoryUsage();

    return 0;
}
