import time
from memory_profiler import memory_usage
from pprint import pprint

t_start = time.perf_counter()

def solution(lines):
    n = int(lines[0])  # количество листов для печати 
    a = []  # список словарей с информацией о цене за листы разного размера 
    for i in range(7): # цикл по количеству строк с ценами за листы разного размера 
        cost = int(lines[i+1]) # цена за 10**i листов

        cost_pro_blatt = cost / (10 ** i) # цена за один лист 
        a.append({"blaetter": 10**i, "cost": cost,
                "cost_pro_blatt": cost_pro_blatt}) # добавление словаря в список 
    
    a = sorted(a, key=lambda x: x["cost_pro_blatt"])    # сортировка списка по цене за лист 
    cost = 0 # итоговая цена
    mini = 10**10 # минимальная цена за лист
    n_ = n # количество листов для печати
    for i in range(7): # цикл по количеству строк с ценами за листы разного размера 
        order = a[i] # словарь с информацией о цене за листы разного размера
        if order["blaetter"] <= n: # если количество листов для печати меньше или равно количеству листов в заказе
            count = (n // order["blaetter"]) # количество заказов с таким количеством листов 
            n -= order["blaetter"] * count # количество листов для печати
            cost += order["cost"] * count # итоговая цена
        if (order["cost"] < mini) and (order["blaetter"] >= n_): # если цена за лист меньше минимальной цены за лист и количество листов в заказе больше или равно количеству листов для печати
            mini = order["cost"] # минимальная цена за лист 

    return cost, mini

with open('/Users/yaroslav/Desktop/лаба по алгосам/2sem/Lab_1/9/input.txt', 'r') as f, open('output.txt', 'w') as out:
    lines = f.readlines()
    res = solution(lines)

    out.write(str(min(res)))

print("время: ", time.perf_counter() - t_start) 
print('память: ', memory_usage())