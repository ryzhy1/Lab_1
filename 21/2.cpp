#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

const int NUM_CARDS_IN_DECK = 36;
const int NUM_CARDS_IN_HAND = NUM_CARDS_IN_DECK / 2;
const string CARD_SUITS = "SHDC";
const string CARD_RANKS = "6789TJQKA";

map<char, int> cards_priority = {
    {'6', 0},
    {'7', 1},
    {'8', 2},
    {'9', 3},
    {'T', 4},
    {'J', 5},
    {'Q', 6},
    {'K', 7},
    {'A', 8},
};

string find_beating_card(const vector<string>& deck, const string& card) {
    for (const auto& c : deck) {
        if (cards_priority[c[0]] > cards_priority[card[0]]) {
            return c;
        }
    }
    return "";
}

int main() {
    ifstream fin("input.txt");

    // Read input from file
    string first_name, last_name, trump_suit;
    fin >> first_name >> last_name >> trump_suit;

    vector<string> deck, hand;
    string card;
    while (fin >> card) {
        if (deck.size() < NUM_CARDS_IN_HAND) {
            deck.push_back(card);
        } else {
            hand.push_back(card);
        }
    }
    fin.close();

    // Sort cards in hand
    sort(hand.begin(), hand.end(), [&](const string& x, const string& y) {
        bool x_is_trump = x[1] == trump_suit[0];
        bool y_is_trump = y[1] == trump_suit[0];

        if (x_is_trump && !y_is_trump) {
            return false;
        } else if (!x_is_trump && y_is_trump) {
            return true;
        } else if (x_is_trump && y_is_trump) {
            return cards_priority[x[0]] > cards_priority[y[0]];
        } else {
            return cards_priority[x[0]] > cards_priority[y[0]];
        }
    });

    // Group cards in deck by suit
    vector<vector<string>> grouped_deck(4);
    for (const auto& card : deck) {
        auto suit_index = CARD_SUITS.find(card[1]);
        grouped_deck[suit_index].push_back(card);
    }

    // Determine if hand can beat the leading card
    for (const auto& card : hand) {
        char rank = card[0], suit = card[1];
        vector<string>& group = grouped_deck[CARD_SUITS.find(suit)];

        string beating_card = find_beating_card(group, card);
        if (!beating_card.empty()) {
            auto it = find(group.begin(), group.end(), beating_card);
            group.erase(it);
            continue;
        }

        beating_card = find_beating_card(grouped_deck[CARD_SUITS.find(trump_suit[0])], card);
        if (!beating_card.empty()) {
            auto it = find(grouped_deck[CARD_SUITS.find(trump_suit[0])].begin(), grouped_deck[CARD_SUITS.find(trump_suit[0])].end(), beating_card);
            grouped_deck[CARD_SUITS.find(trump_suit[0])].erase(it);
            continue;
        }

        cout << "NO" << endl;
        return 0;
    }

    cout << "YES";
}
