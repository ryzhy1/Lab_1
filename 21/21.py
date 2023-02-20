from itertools import groupby
from typing import Dict, List, Tuple

cards_priority = {
    "6": 0,
    "7": 1,
    "8": 2,
    "9": 3,
    "T": 4,
    "J": 5,
    "Q": 6,
    "K": 7,
    "A": 8,
}

def beat(deck: List[Tuple[str, str]], card: Tuple[str, str]) -> Tuple[str, str]:
    return min((c for c in deck if cards_priority[c[0]] > cards_priority[card[0]]), default=None)

def main(R, cards, sorted_deck) -> None:
    
    for card in cards:
        val, suit = card
        if suit != R:
            res = beat(sorted_deck[suit], card)
            if res is not None:
                sorted_deck[suit].remove(res)
                continue
        res = beat(sorted_deck[R], card) if suit == R else sorted_deck[R][0] if sorted_deck[R] else None
        if res is not None:
            sorted_deck[R].remove(res)
            continue
        return("NO")
        quit()
    return("YES")

if __name__ == '__main__':
    with open('input.txt') as f, open('output.txt', 'w') as out:
        N, M, R = f.readline().split()
        handss = f.readline()
        cardss = f.readline()

        hands = sorted([(i[0], i[1]) for i in handss.split()], key=lambda x: (x[1] != R, cards_priority[x[0]]))
        cards = sorted([(i[0], i[1]) for i in cardss.split()], key=lambda x: (x[1] != R, cards_priority[x[0]]))
        sorted_deck = {key: list(items) for key, items in groupby(hands, lambda x: x[1])}

        res = main(R, cards, sorted_deck)
        out.write(res)