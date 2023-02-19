import time
from memory_profiler import memory_usage

start_time = time.time()

def anti_quick_sort(n):

    arr = [0] * n
    for i in range(n):
        arr[i] = i + 1

    for i in range(2, n):
        arr[i], arr[i // 2] = arr[i // 2], arr[i]

    arr_res = []
    for i in arr:
        arr_res.append(i)

    return arr_res[::-1]

with open('input.txt') as f:
    n = int(f.readline())


with open('output.txt', 'w') as out:
    out.write(" ".join(map(str, anti_quick_sort(n))))


print("Время: ", (time.time() - start_time))
print("Память: ", memory_usage())