#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    string s;
    fin >> s;

    // Стек для хранения открывающих скобок
    stack<pair<char, int> > st;

    // Вектор для хранения помеченных скобок
    vector<bool> is_deleted(s.size(), false);

    // Проходим по строке
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            st.push(make_pair(c, i));
        } else if (c == ')') {
            if (st.empty() || st.top().first != '(') {
                is_deleted[i] = true;
            } else {
                st.pop();
            }
        } else if (c == ']') {
            if (st.empty() || st.top().first != '[') {
                is_deleted[i] = true;
            } else {
                st.pop();
            }
        } else if (c == '}') {
            if (st.empty() || st.top().first != '{') {
                is_deleted[i] = true;
            } else {
                st.pop();
            }
        }
    }

    // Помечаем оставшиеся скобки как неудаляемые
    while (!st.empty()) {
        is_deleted[st.top().second] = true;
        st.pop();
    }

    // Строим новую строку, не включая помеченные скобки
    string result;
    for (int i = 0; i < s.size(); i++) {
        if (!is_deleted[i]) {
            result += s[i];
        }
    }

    fout << result << endl;
    return 0;
}
