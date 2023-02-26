#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <string>
#include <vector>

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

    vector<int> nums;
    int n, a;
    fin >> n;

    for (int i = 0; i < n; i ++){
        int a;
        fin >> a;
        nums.push_back(a);
    }

    for (int i = 0; i < n; i++) {   
        int maxi = 0;
        for (auto num : nums) {
            if (num > maxi) {
                maxi = num;
            }
        }
        fout << to_string(maxi);
        nums.erase(find(nums.begin(), nums.end(), maxi));
        maxi = 0;
    }
    printTimeUse();
    printMemoryUsage();
    return 0;
}