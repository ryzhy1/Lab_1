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

    vector <vector <int>> a(n, vector <int>(n));
    for(int i = 0; i < n; ++ i)
        for(int j = 0; j < n; ++ j)
            fin >> a[i][j];

    vector <vector <int> > dp ((1ll << n), vector <int> (n, 1e9));
    vector <vector <int> > parent ((1ll << n), vector <int> (n, -1));
    for(int i = 0; i < n; ++ i)
        dp[(1 << i)][i] = 0;

    for(int i = 0; i < (1ll << n); ++ i) {
        for(int j = 0; j < n; ++ j) {
            if(!(i & (1ll << j)))
                continue;

            for(int k = 0; k < n; ++ k) {
                if((i & (1 << k)))
                    continue;

                dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + a[j][k]);
                if(dp[i | (1 << k)][k] == dp[i][j] + a[j][k])
                    parent[i | (1 << k)][k] = j;
            }
        }
    }

    int minimum = 1e9, lastparent = -1, curmask = (1 << n) - 1;
    vector <int> ans;
    for(int i = 0; i < n; ++ i) {
        if(dp[curmask][i] < minimum) {
            minimum = dp[curmask][i];
            lastparent = i;
        }
    }

    while(lastparent != -1) {
        ans.push_back(lastparent);
        int newmask = curmask ^ (1 << lastparent);
        lastparent = parent[curmask][lastparent];
        curmask = newmask;
    }

    fout << minimum << '\n';
    for(int i = ans.size() - 1; i >= 0; -- i)
        fout << " " << ans[i] + 1;
    // ---- code ends here -----

    printTimeUse();
    printMemoryUsage();

    fin.close();
    fout.close();
    return 0;
}
