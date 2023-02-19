from itertools import groupby

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

def beat(deck, card):
    return min((c for c in deck if cards_priority[c[0]] > cards_priority[card[0]]), default=None)

with open("input.txt") as f, open('output.txt', 'w') as out:
    _, _, trump = f.readline().split()
    deck = sorted([(i[0], i[1]) for i in f.readline().split()], key=lambda x: (x[1] != trump, cards_priority[x[0]]))
    cards = sorted([(i[0], i[1]) for i in f.readline().split()], key=lambda x: (x[1] != trump, cards_priority[x[0]]))
    grouped_deck = {key: list(items) for key, items in groupby(deck, lambda x: x[1])}

    for card in cards:
        val, suit = card
        if suit != trump:
            res = beat(grouped_deck[suit], card)
            if res is not None:
                grouped_deck[suit].remove(res)
                continue
        res = beat(grouped_deck[trump], card) if suit == trump else grouped_deck[trump][0] if grouped_deck[trump] else None
        if res is not None:
            grouped_deck[trump].remove(res)
            continue
        out.write("NO")
        quit()
    out.write("YES")
