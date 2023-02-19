#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <time.h>
#include <iomanip>
#include <math.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

map<char, int> cards_priority = {
	{'6', 0},
	{'7', 1},
	{'8', 2},
	{'9', 3},
	{'T', 5},
	{'J', 6},
	{'Q', 7},
	{'K', 8},
	{'A', 9},
};

// string can_defeat(deck, card) {
// 	for (auto& )
// }

bool compareCards(const string& x, const string& y, const string& R) {
    bool x_is_trump = x[1] == R[0];
    bool y_is_trump = y[1] == R[0];

    if (x_is_trump && !y_is_trump) {
        return false;
    } else if (!x_is_trump && y_is_trump) {
        return true;
    } else if (x_is_trump && y_is_trump) {
        return cards_priority[x[0]] > cards_priority[y[0]];
    } else {
        return cards_priority[x[0]] > cards_priority[y[0]];
    }
}


int main() {

	int N, M;
	string R, card;
	fin >> N >> M >> R;

	vector<string> hand, deck;

	while (fin >> card) {
		if (hand.size() < N) {
			hand.push_back(card);
		} else {
			deck.push_back(card);
		}
	}

	sort(hand.begin(), hand.end(), compareCards);
	sort(deck.begin(), deck.end(), compareCards);

	for (int i = 0; i < hand.size(); i ++) {
		cout << hand[i] << endl;
	}

}