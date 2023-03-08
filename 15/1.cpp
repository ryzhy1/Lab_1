#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <fstream>

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

    string s;
    fin >> s;

    // Стек для хранения открывающих скобок
    stack<pair<char, int> > st;

    // Вектор для хранения помеченных скобок
    vector<bool> marked(s.size(), false);

    // Проходим по строке
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            st.push(make_pair(c, i));
        } else if (c == ')') {
            if (st.empty() || st.top().first != '(') {
                marked[i] = true;
            } else {
                st.pop();
            }
        } else if (c == ']') {
            if (st.empty() || st.top().first != '[') {
                marked[i] = true;
            } else {
                st.pop();
            }
        } else if (c == '}') {
            if (st.empty() || st.top().first != '{') {
                marked[i] = true;
            } else {
                st.pop();
            }
        }
    }

    // Помечаем оставшиеся скобки как неудаляемые
    while (!st.empty()) {
        marked[st.top().second] = true;
        st.pop();
    }

    // Строим новую строку, не включая помеченные скобки
    string result;
    for (int i = 0; i < s.size(); i++) {
        if (!marked[i]) {
            result += s[i];
        }
    }

    fout << result << endl;
    printTimeUse();
    printMemoryUsage();

    return 0;
}
