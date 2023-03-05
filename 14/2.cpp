#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int calculate(vector<int>& nums, vector<char>& ops) {
    int res = nums[0];
    for (int i = 0; i < ops.size(); i++) {
        if (ops[i] == '+') res += nums[i+1];
        else if (ops[i] == '-') res -= nums[i+1];
        else if (ops[i] == '*') res *= nums[i+1];
    }
    return res;
}

void generate(vector<int>& nums, vector<char>& ops, vector<bool>& used, int& res) {
    if (ops.size() == nums.size() - 1) {
        res = max(res, calculate(nums, ops));
        return;
    }
    for (int i = 0; i < nums.size() - 1; i++) {
        if (!used[i]) {
            used[i] = true;
            ops.push_back('+');
            generate(nums, ops, used, res);
            ops.back() = '-';
            generate(nums, ops, used, res);
            ops.back() = '*';
            generate(nums, ops, used, res);
            ops.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    ifstream fin("input.txt");
    string s;
    getline(fin, s);
    int n = s.size() / 2 + 1;
    vector<int> nums(n);
    vector<char> ops(n-1, '+'); // начинаем с массива из всех сложений
    for (char i : s) {
        if (i == '+' || i == '*' || i == '-') {
            ops.push_back(i);
        } else {
            nums.push_back(i - '0');
        }
    }
    vector<bool> used(n-1);
    int res = calculate(nums, ops); // начальное значение res
    generate(nums, ops, used, res);
    ofstream fout("output.txt");
    fout << res << endl;
    return 0;
}
