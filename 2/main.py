with open('input.txt', 'r') as f, open('output.txt', 'w') as out:
    d = int(f.readline())
    m = int(f.readline())
    n = int(f.readline())
    stops = list(map(int, fin.readline().split()))

    stops.append(d)
    stops.sort()

    current_stop = 0
    current_fuel = m
    result = 0

    for i in range(len(stops)):
        if stops[i] - current_stop > current_fuel:
            if stops[i] - stops[i-1] > m:
                result = -1
                break
            current_stop = stops[i-1]
            current_fuel = m
            result += 1
        current_fuel -= stops[i] - current_stop
        current_stop = stops[i]
    out.write(str(result))
