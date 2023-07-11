from functools import reduce
import sys


if __name__ == '__main__':
    req = sys.stdin.readline().split()

    q = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]

    firstday = q.index(req[1])

    print(".. " * firstday +
          reduce(lambda x, n: x + str(n), ["." + str(i) + " " for i in range(1, 7 - firstday + 1)]))

    i = 7 - firstday + 1
    while i < int(req[0]) + 1:
        print(reduce(lambda x, n: x + str(n),
                     [("" if len(str(i)) > 1 else ".") + str(i) + " "
                      for i in range(i, min(i + 7, int(req[0]) + 1))]))
        i += 7
