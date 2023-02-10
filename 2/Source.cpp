#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <iomanip>
#include "windows.h"
#include "psapi.h"

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

clock_t start;

void printMemoryUse() {
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

	cout << fixed << setprecision(6);
	cout << "Memory used: " << double(virtualMemUsedByMe) / (1024. * 1024) << " MB\n";
}

void getFirstTime() {
	start = clock();
}

void printTimeUse() {
	cout << "Time used: " << (double)(clock() - start) / CLOCKS_PER_SEC << " sec\n";
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
	printMemoryUse();
	
}