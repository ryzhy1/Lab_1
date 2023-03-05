f = open('input.txt')
f1 = open('output.txt', 'w')

n = int(f.readline()) + 1
inf = 10 ** 9

a = [[inf] * n for i in range(n)]

ln = 1 << n

dp = [[inf] * ln for _ in range(n)]

for i in range(n):
    if i != 0:
        tmp = list(map(int, f.readline().split()))
        k = 0
    for j in range(n):
        if i == 0 and j == 0:
            a[i][j] = 0
            continue
        if i == 0 or j == 0:
            a[i][j] = -1
        else:
            a[i][j] = tmp[k]
            k += 1

print(*a, sep='\n')


def ans(i, j):
    if i == 0 and j == 0:
        return 0
    if dp[i][j] != inf:
        return dp[i][j]

    for e in range(n):
        if (j & (1 << e)) == 0:
            bit = False
        else:
            bit = True
        if a[i][e] != 0 and bit:
            dp[i][j] = min(dp[i][j], ans(e, j - (1 << e)) + a[i][e])
    return dp[i][j]


res = ans(0, ln - 1)
print(str(res + 2))

restored = []
i = 0
j = ln - 1

while j != 0:
    for k in range(n):
        if (j & (1 << k)) == 0:
            bit = False
        else:
            bit = True
        if (a[i][k] != 0) and bit and (dp[i][j] == dp[k][j - (1 << k)] + a[i][k]) or (j - (1 << k) == 0):
            restored.append(k)
            i = k
            j = j - (1 << k)

print(restored[n - 2::-1])
