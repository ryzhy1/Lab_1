import typing as tp

import time
import tracemalloc


def get_sequence_partition_sum(sequence: tp.List[int]) -> tp.Optional[int]:
    length = len(sequence)

    sequence_sum = sum(sequence)
    if sequence_sum % 2 != 0:
        return None

    partition_sum = sequence_sum // 2
    dp = [[False for _ in range(partition_sum + 1)] for _ in range(length + 1)]
    for i in range(length + 1):
        dp[i][0] = True

    for i in range(1, length + 1):
        for j in range(1, partition_sum + 1):
            if j < sequence[i - 1]:
                dp[i][j] = dp[i - 1][j]
            else:
                dp[i][j] = dp[i - 1][j] or dp[i - 1][j - sequence[i - 1]]

    if dp[length][partition_sum]:
        return partition_sum

    return None


if __name__ == "__main__":
    start_time = time.perf_counter()
    tracemalloc.start()

    # Код
    with open("input.txt") as inp_file, open("output.txt", "w") as out_file:
        _, sequence = inp_file.readlines()
        word = inp_file.readline()

        partition_sum = get_sequence_partition_sum(
            [int(number.strip()) for number in sequence.split()]
        )

        if partition_sum is not None:
            out_file.write(f"1\n{partition_sum}")
        else:
            out_file.write(f"-1")

    _, peak = tracemalloc.get_traced_memory()
    print(
        "Время работы в секунда %s" % (time.perf_counter() - start_time),
        f"Пиковое значение памяти {peak / 1024}KB",
    )
    tracemalloc.stop()
