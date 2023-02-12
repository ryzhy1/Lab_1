#include <iostream>
#include <fstream>
#include <iomanip>
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

	int n, W;
	fin >> n >> W;

	int* p = new int[n];
	int* w = new int[n];
	double* pw = new double[n];


	for (int i = 0; i < n; i++) {
		fin >> p[i] >> w[i];
	}

	for (int i = 0; i < n; i++) {
		pw[i] = (double)p[i] / w[i];
	}

	int maxIndex = 0;
	double maxRatio = 0;
	double sum = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (pw[j] > maxRatio) {
				maxRatio = pw[j];
				maxIndex = j;
			}
		}

		if (w[maxIndex] < W) {
			sum += p[maxIndex];
			W -= w[maxIndex];
		}
		else {
			sum += (double)W * pw[maxIndex];
			W = 0;
		}

		pw[maxIndex] = 0;
		maxRatio = 0;
	}
	fout << fixed << setprecision(4) << sum;
	printTimeUse();
	getMemoryUsage();

	return 0;
}