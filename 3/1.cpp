#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sys/time.h>
#include <mach/task.h>
#include <mach/mach_init.h>
#include <cmath>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

clock_t start;

void getMemoryUsage() {
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
    getMemoryUsage();
    return 0;
}