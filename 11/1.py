from pprint import pprint

def knapsack(W, n, w):
        dp = [[0 for j in range(W+1)] for i in range(n+1)]
        for i in range(1, n+1):
            for j in range(1, W+1):
                if w[i-1] > j:
                    dp[i][j] = dp[i-1][j]
                else:
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i-1]]+w[i-1])
        pprint(dp) 
        return dp[n][W]

with open("input.txt") as f, open("output.txt", "w") as out:

    W, n = map(int, f.readline().split())
    w = list(map(int, f.readline().split()))

    res = knapsack(W, n, w);


    out.write(str(res))