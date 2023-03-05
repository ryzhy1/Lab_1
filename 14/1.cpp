#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>

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

pair<int, int> MinandMax(int i, int j, vector<vector<int>>& M, vector<char>& op) {
    int mn = INT_MAX, mx = INT_MIN;
    for (int k = i; k < j; k++) {
        int a = 0, b = 0, c = 0, d = 0;
        if (op[k] == '*') {
            a = M[i][k] * M[k + 1][j];
            cout << M[i][k] << op[k] << M[k + 1][j] << " = " << M[i][k] * M[k + 1][j] << endl;
        } else if (op[k] == '+') {
            a = M[i][k] + M[k + 1][j];
            cout << M[i][k] << op[k] << M[k + 1][j] << " = " << M[i][k] + M[k + 1][j] << endl;
        } else {
            a = M[i][k] - M[k + 1][j];
            cout << M[i][k] << op[k] << M[k + 1][j] << " = " << M[i][k] - M[k + 1][j] << endl;
        }
        mn = min(mn, min(a, min(b, min(c, d))));
        mx = max(mx, max(a, max(b, max(c, d))));
    }
    return {mn, mx};
}

int maxValue(vector<int>& d, vector<char>& op) {
    int n = d.size();
    vector<vector<int>> M(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        M[i][i] = d[i];
    }
    for (int s = 1; s < n; s++) {
        for (int i = 0; i < n - s; i++) {
            int j = i + s;
            auto [min_val, max_val] = MinandMax(i, j, M, op);
            M[i][j] = max_val;
        }
        
    }
    return M[0][n - 1];
}

int main() {
    string str1;
    getline(fin, str1);
    vector<int> d;
    vector<char> op;
    for (char i : str1) {
        if (i == '+' || i == '*' || i == '-') {
            op.push_back(i);
        } else {
            d.push_back(i - '0');
        }
    }
    int answer = maxValue(d, op);
    fout << answer;
    return 0;
}