#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <type_traits>

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

//------------------------------------

int main() {
    getFirstTime();

    // ---- code starts here -----

    int n;
    fin >> n;

    vector <int> a (n);
    for(auto &i : a)
        fin >> i;

    int sum = 0;
    for(auto &i : a)
        sum += i;

    if(sum % 3) {
        fout << 0;
        return 0;
    }

    vector <int> test (2 * sum / 3);

    for(int i = 0; i < (1ll << n); i++) {
        int sum1 = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1ll << j))
                sum1 += a[j];
        }

        if (sum1 == sum / 3) { // 
            int cur = 0;
            for (int j = 0; j < n; ++j) {
                if (!(i & (1ll << j)))
                    test[cur++] = a[j];
            }

            for (int j = 0; j < (1ll << cur); j++) {
                int sum2 = 0;
                for (int k = 0; k < cur; ++k) {
                    if (j & (1ll << k))
                        sum2 += test[k];
                }

                if (sum2 == sum / 3) {
                    fout << 1;
                    printTimeUse();
                    printMemoryUsage();
                    return 0;
                }
            }
        }
    }

    fout << 0;


    // ---- code ends here -----

    printTimeUse();
    printMemoryUsage();

    fin.close();
    fout.close();
    return 0;
}
