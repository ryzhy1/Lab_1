#include <iostream>
#include <fstream>
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

	fout << sum;
	printTimeUse();
	printMemoryUse();

	return 0;
}