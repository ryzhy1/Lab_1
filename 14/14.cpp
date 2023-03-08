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

int best_res(int i, int j, const string &s, bool isMax = true) {
    if (i == j) {
        return s[i] - '0';
    }

    if(isMax) {
        int ans = -1e9;

        for (int k = i; k < j; ++k) {
            if (s[k] == '+')
                ans = max(ans, best_res(i, k - 1, s) + best_res(k + 1, j, s));
            else if (s[k] == '-')
                ans = max(ans, best_res(i, k - 1, s) - best_res(k + 1, j, s, 0));
            else if(s[k] == '*')
                ans = max(ans, best_res(i, k - 1, s) * best_res(k + 1, j, s));
        }

        return ans;
    } else {
        int ans = 1e9;

        for (int k = i; k < j; ++k) {
            if (s[k] == '+')
                ans = min(ans, best_res(i, k - 1, s, 0) + best_res(k + 1, j, s, 0));
            else if (s[k] == '-')
                ans = min(ans, best_res(i, k - 1, s, 0) - best_res(k + 1, j, s, 1));
            else if(s[k] == '*')
                ans = min(ans, best_res(i, k - 1, s, 0) * best_res(k + 1, j, s, 0));
        }

        return ans;
    }
}


int main() {
    getFirstTime();

    // ---- code starts here -----

    string s;
    fin >> s;

    fout << best_res(0, s.size() - 1, s);

    // ---- code ends here -----

    printTimeUse();
    printMemoryUsage();

    fin.close();
    fout.close();
    return 0;
}
