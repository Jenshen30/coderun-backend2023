from math import factorial


def comb(n, k):
    return factorial(n) / (factorial(k) * factorial(n - k))


def countGood(n):
    odd = 0
    div5 = 0
    summary = 0
    for ch in n:
        num = int(ch)
        summary += num

        if num % 5 == 0:
            div5 += 1
        if num % 2 == 0:
            odd += 1
    div6 = (summary % 3 == 0)
    return div6, div5 + (odd if div6 else 0)


def initCheck(n, isDiv6):
    return int(n[-1]) % 5 == 0 or (isDiv6 and int(n[-1]) % 2 == 0)


def main(n, k):
    dp = [[-1.0, -1.0] for i in range(k + 1)]
    isDiv6, c = countGood(n)

    dp[0][1] = float(initCheck(n, isDiv6))
    dp[0][0] = 1.0 - dp[0][1]

    for i in range(1, k + 1):
        dp[i][1] = dp[i - 1][1] * (len(n) - 2) / (len(n)) +\
                   dp[i - 1][0] * (2 * c / (len(n) * (len(n) - 1))) +\
                   dp[i - 1][1] * (2 * (c - 1) / (len(n) * (len(n) - 1)))

        dp[i][0] = 1.0 - dp[i][1]

    return dp[k][1]


if __name__ == '__main__':
    n = str(input())
    k = int(input())
    print(main(n , k))