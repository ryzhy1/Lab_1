#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sys/time.h>
#include <mach/task.h>
#include <mach/mach_init.h>

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

	int K, n;
	fin >> K >> n;

	vector<int> shoes;

	for (int i = 0; i < n; i++) {
		int k;
		fin >> k;
		shoes.push_back(k);
	}

	sort(shoes.begin(), shoes.end());

	int sum = 0;
	int count = 0;

	for (int i = 0; i < n; i++) {
		if (sum + shoes[i] < K) {
			sum += shoes[i];
			count += 1;
		}
	}
	
	fout << count;
	printTimeUse();
	getMemoryUsage();
	
}