#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> get_natural_numbers_sum(int n, int current_sum=0, vector<int> current_list={}, int current_num=1) {
    if (current_sum == n) {
        return current_list;
    } else if (current_sum > n) {
        return {};
    }

    for (int num = current_num; num <= n - current_sum + 1; num ++) {
        auto result = get_natural_numbers_sum(n, current_sum + num, current_list);
        result.push_back(num);

        if (!result.empty()) {
            return result;
        }
    }
    return {};
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;

    auto natural_numbers_sum = get_natural_numbers_sum(n);

    fout << natural_numbers_sum.size() << endl;
    for (int num : natural_numbers_sum) {
        fout << num << " ";
    }
    fout << endl;

    fin.close();
    fin.close();
    
    return 0;
}
