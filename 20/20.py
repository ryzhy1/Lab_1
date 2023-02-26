import typing as tp

import time
import tracemalloc


def get_almost_palindrom_count(word: str, k: int):
    char_changes = [[0 for _ in range(len(word))] for _ in range(len(word))]

    counter = 0
    for length in range(1, len(word) + 1):
        for i in range(len(word) - length + 1):
            j = i + length - 1
            if length == 1:
                char_changes[i][j] = 0
            elif length == 2:
                char_changes[i][j] = int(word[i] != word[j])
            else:
                char_changes[i][j] = char_changes[i + 1][j - 1] + int(
                    word[i] != word[j]
                )

            if char_changes[i][j] <= k:
                counter += 1

    return counter


if __name__ == "__main__":
    start_time = time.perf_counter()
    tracemalloc.start()

    # Код
    with open("input.txt") as inp_file, open("output.txt", "w") as out_file:
        k = int(inp_file.readline().strip().split()[-1])
        word = inp_file.readline()

        almost_palindrom_count = get_almost_palindrom_count(word, k)
        out_file.write(str(almost_palindrom_count))

    _, peak = tracemalloc.get_traced_memory()
    print(
        "Время работы в секунда %s" % (time.perf_counter() - start_time),
        f"Пиковое значение памяти {peak / 1024}KB",
    )
    tracemalloc.stop()
