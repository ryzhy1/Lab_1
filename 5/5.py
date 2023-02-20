import typing as tp

import time


def get_natural_numbers_sum(n, current_sum=0, current_list=[], current_num=1):
    if current_sum == n:
        return current_list
    elif current_sum > n:
        return None

    for num in range(current_num, n - current_sum + 1):
        result = get_natural_numbers_sum(
            n, current_sum + num, current_list + [num], num + 1
        )

        if result is not None:
            return result


if __name__ == "__main__":
    start_time = time.perf_counter()
    

    # Код
    with open("input.txt") as inp_file, open("output.txt", "w") as out_file:
        n = int(inp_file.readline())
        natural_numbers_sum = get_natural_numbers_sum(8)

        output_data = f"{len(natural_numbers_sum)}\n" + " ".join(
            map(str, natural_numbers_sum)
        )

        out_file.write(output_data)

print("Время: ", time.perf_counter() - start_time)