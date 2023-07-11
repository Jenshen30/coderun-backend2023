import sys


def createCategoryList(ids, l):
    ans = []
    for el in ids:
        ans.append(findCategory(el, l))
    return ans


def findCategory(id, l):
    return l.get(id)


def findMin(categories):
    global n
    was = dict()
    mini = n

    for i in range(0, len(categories)):
        if was.get(categories[i]) is not None:
            mini = min(mini, i - was.get(categories[i]))
        was[categories[i]] = i
    return mini


if __name__ == '__main__':
    n = int(sys.stdin.readline())
    l = dict()

    for _ in range(n):
        tmp = tuple(map(int, sys.stdin.readline().split()))
        l[tmp[0]] = tmp[1]

    ids = list(map(int, sys.stdin.readline().split()))
    categories = createCategoryList(ids, l)
    print(findMin(categories))


