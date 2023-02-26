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

// --------------- code ---------------

int maxLectures(vector<int>& begins, vector<int>& ends, int lecturesAmount) {
    int lastLect = 0, minTimeLectListen = 0, count = 0;

    while (minTimeLectListen < 1440) {
        minTimeLectListen = 1440;

        for (int i = 0; i < lecturesAmount; i++) {
            if (begins[i] >= lastLect && ends[i] < minTimeLectListen) {
                minTimeLectListen = ends[i];
            }
        }   

        if (minTimeLectListen < 1440) {
            lastLect = minTimeLectListen;
            count++;
        }
    }

    return count;
}

int main() {
    getFirstTime();

    vector<pair<int, int> > segments;
    int n;
    fin >> n;

    vector<int> begins;
    vector<int> ends;



    for (int i = 0; i < n; i++) {
        int s, f;
        fin >> s >> f;
        begins.push_back(s);
        ends.push_back(f);
    }

    fout << maxLectures(begins, ends, n);
    printTimeUse();
    printMemoryUsage();

    return 0;
}