#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

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

struct Apple {
    int a, b, id;
};

bool compare_apples(const Apple& x, const Apple& y) {
    return x.b > y.b;
}

int main() {
    getFirstTime();

    int n, s;
    fin >> n >> s;
    vector<Apple> apples(n);
    for (int i = 0; i < n; i++) {
        fin >> apples[i].a >> apples[i].b;
        apples[i].b -= apples[i].a;
        apples[i].id = i + 1;
    }

    sort(apples.begin(), apples.end(), compare_apples);

    vector<int> order;
    while (!apples.empty()) {
        bool possible = false;
        for (int i = 0; i < apples.size(); i++) {
            if (s - apples[i].a > 0) {
                s += apples[i].b;
                order.push_back(apples[i].id);
                apples.erase(apples.begin() + i);
                possible = true;
                break;
            }
        }
        if (!possible) {
            fout << -1 << endl;
            return 0;
        }
    }

    for (int i = 0; i < order.size(); i++) {
        fout << order[i] << " ";
    }
    fout << endl;
    printTimeUse();
    printMemoryUsage();

    return 0;
}