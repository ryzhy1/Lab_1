with open('input14.txt') as file:
    str1 = file.readline()
d, op, m, M = [], [], [], []
for i in str1:
    if i == "+" or i == "*" or i == "-":
        op.append(i)
    else:
        d.append(int(i))
def MinandMax(i, j, m, M, op):
    minimum1 = float("+inf")
    maximum1 = float("-inf")
    for k in range(i, j):
        if op[k] == '*':
            a = M[i][k] * M[k + 1][j]
            b = M[i][k] * m[k + 1][j]
            c = m[i][k] * M[k + 1][j]
            d = m[i][k] * m[k + 1][j]
        elif op[k] == '+':
            a = M[i][k] + M[k + 1][j]
            b = M[i][k] + m[k + 1][j]
            c = m[i][k] + M[k + 1][j]
            d = m[i][k] + m[k + 1][j]
        else:
            a = M[i][k] - M[k + 1][j]
            b = M[i][k] - m[k + 1][j]
            c = m[i][k] - M[k + 1][j]
            d = m[i][k] - m[k + 1][j]
        minimum1 = min(minimum1, a, b, c, d)
        maximum1 = max(maximum1, a, b, c, d)
    return minimum1, maximum1
def maxValue(d, op):
    n = len(d)
    m = []
    M = []
    for i in range(len(d)):
        m.append([])
        M.append([])
        for j in range(len(d)):
            m[i].append(0)
            M[i].append(0)
    for i in range(n):
        m[i][i] = d[i]
        M[i][i] = d[i]
    for s in range(1, n):
        for i in range(n - s):
            j = i + s
            m[i][j], M[i][j] = MinandMax(i, j, m, M, op)
    return M[0][n - 1]
answer = maxValue(d, op)
with open("output14.txt", "w") as f:
    f.write(str(answer))