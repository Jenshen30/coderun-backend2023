import sys


def main():
    n, m = map(int, input().split())
    a = sorted(list(map(int, input().split())))
    b = sorted(list(map(int, input().split())))
    b.reverse()
    s = 0
    j = len(b) - 1
    for i in range(len(a)):
        if i >= len(b):
            break
        s += max(b[i] - a[i], 0)
    print(s)


if __name__ == '__main__':
    main()
"""
2 3
1 1
3 3 3

6 5
5 10 8 4 7 2
3 1 11 18 9



"""