import math

EPS = 10 ** -10
CORDS = [[0, 0], -100, [0, 1], -100, [1, 1], -100, [1, 0]]


def findYs(x, r, dot):
    if (r ** 2) - (x - dot[0]) ** 2 <= EPS:
        return None
    c = math.pow(r ** 2 - (x - dot[0]) ** 2, 0.5)
    return [(x, c + dot[1]),
            (x, -c + dot[1])]


def where(dots, f, s, XOrY):
    if dots is None:
        return []
    ans = []
    if dots[0][XOrY] - 1 >= EPS:
        ans.append([dots[0], f])
    if dots[1][XOrY] <= EPS:
        ans.append([dots[1], s])
    return ans


def findXs(y, r, dot):
    if (r ** 2) - (y - dot[1]) ** 2 <= EPS:
        return None
    c = math.pow(r ** 2 - (y - dot[1]) ** 2, 0.5)
    return [(c + dot[0], y),
            (-c + dot[0], y)]


def cos(v1, v2):
    return (v1[0] * v2[0] + v1[1] * v2[1]) / \
           math.pow((v1[0] ** 2 + v1[1] ** 2) * (v2[0] ** 2 + v2[1] ** 2), 0.5)


# x = 0, 1
# y = 0, 1
# fixme в углу повторы
def findOposite(check, i):
    for j in range(0, len(check)):
        if check[j][1] == i + 1 and i % 2 == 0:
            return j
    return -1


def findReal(check, i):
    for j in range(0, len(check)):
        if check[j][1] == i:
            return j


def searchDublicates(check, dot):
    s = 0
    for _ in range(0, 7, 2):
        i = findReal(check, _)
        ind = findOposite(check, _)
        if ind == -1 or (i is None):
            continue
        v1, v2 = (check[i][0][0] - dot[0], check[i][0][1] - dot[1]), \
                 (check[ind][0][0] - dot[0], check[ind][0][1] - dot[1])
        angleRad = math.acos(cos(v1, v2))

        s += (r ** 2) * (angleRad - math.sin(angleRad))
        # triangle

        c1 = (CORDS[_][0] - check[i][0][0]) ** 2 + (CORDS[_][1] - check[i][0][1]) ** 2
        c2 = (CORDS[_][0] - check[ind][0][0]) ** 2 + (CORDS[_][1] - check[ind][0][1]) ** 2

        s += math.pow(c1 * c2, 0.5)
    return s


def findSquare(r, dot):
    above = [findXs(0, r, dot), findXs(1, r, dot),
             findYs(0, r, dot), findYs(1, r, dot)]

    s_extra = 0

    # extra square
    for dots in above:
        if dots is None:
            continue
        v1, v2 = (dots[0][0] - dot[0], dots[0][1] - dot[1]),\
                 (dots[1][0] - dot[0], dots[1][1] - dot[1])
        angleRad = math.acos(cos(v1, v2))
        s_extra += (r ** 2) * (angleRad - math.sin(angleRad))

    # add dots from duplicated parts
    check = []

    # last 2 params to order them
    check += where(findYs(0, r, dot), 3, 0, 1)
    check += where(findYs(1, r, dot), 4, 7, 1)

    check += where(findXs(0, r, dot), 6, 1, 0)
    check += where(findXs(1, r, dot), 5, 2, 0)

    return math.pi * r ** 2 + 0.5 * (-s_extra + searchDublicates(check, dot))


if __name__ == '__main__':
    n, r = map(float, input().split())
    centers = []
    ans = 0
    for _ in range(int(n)):
        ans += \
            findSquare(r, tuple(map(float, input().split())))

    print(ans)

"""
1 0.4472135
0 0.5

0.3141591311850913611401722665245238759666607683446304653886196439726466843376070228074894075322807961

1 0.4472135
1 0.5


1 0.6
0.5 0
-> 0.520471
(0.0225078) - с одной стороны лишнее
(0.565487) - нижний ненужный кусок
"""