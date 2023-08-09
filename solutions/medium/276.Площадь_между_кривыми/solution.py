EPS = 10 ** -9


def F_q(a, b, c, x):
    return (2 * a * (x ** 3) +
            3 * b * (x ** 2) + 6 * c * x) / 6


def f_l(coords, x):
    return coords[1] * x * x / 2 +\
           coords[2] * x


def isEquals(a, b):
    return abs(a - b) < EPS


def greater(a, b):
    return a - b > EPS


def lower(a, b):
    return a - b < EPS


def index(coords):
    if isEquals(coords[0], 0) and isEquals(coords[1], 0):
        return 0# const
    if isEquals(coords[0], 0):
        return 1# linear
    return 2# quadric


def isTwoRoots(coords):
    # optional >=
    return greater(coords[1] * coords[1] - 4 * coords[0] * coords[2], 0)


def roots(coords):
    d = coords[1] * coords[1] - 4 * coords[0] * coords[2]
    return [(-coords[1] - d ** 0.5) / (2 * coords[0]),
            (-coords[1] + d ** 0.5) / (2 * coords[0])]


# D < 0 - wa
def quadric(a, b, coords):
    if not isTwoRoots(coords):
        return abs(F_q(coords[0], coords[1], coords[2], b) -
                F_q(coords[0], coords[1], coords[2], a))
    else:
        dots = roots(coords)
        dots.append(a)
        dots.append(b)
        dots.sort()

        ans = 0
        flag = False

        for i in range(0, len(dots) - 1):
            if isEquals(dots[i], b):
                break

            if isEquals(dots[i], a) or flag:
                flag = True
                ans += abs(F_q(coords[0], coords[1], coords[2], dots[i + 1]) -
                        F_q(coords[0], coords[1], coords[2], dots[i]))

        return ans


def linear(a, b, coords):
    root = -coords[2] / coords[1]

    if greater(root, a) and greater(b, root):
        return linear(a, root, coords) + linear(root, b, coords)

    return abs(f_l(coords, b) - f_l(coords, a))


def const(a, b, coords):
    #assert True
    return abs((b - a) * coords[2])


def calculate(a, b, coords: list):
    funcs = {
        0: const,
        1: linear,
        2: quadric
    }
    return funcs.get(index(coords))(a, b, coords)


# f: (a1, b1, c1) g:(a2, b2, c2) -> massF[i] - massG[i]
def get_coord(triple_first, triple_second, quadric_1, quadric_2, param):
    return triple_first[quadric_1][param] - triple_second[quadric_2][param]


def main():
    n, m = map(int, input().split())
    mass_first = list(map(int, input().split()))
    triple_first = []

    for i in range(n):
        triple_first.append(tuple(map(int, input().split())))

    mass_second = list(map(int, input().split()))

    triple_second = []

    for j in range(m):
        triple_second.append(tuple(map(int, input().split())))

    quadric_1 = 0
    quadric_2 = 0

    end = mass_first[0]
    ans = 0

    i = 1
    j = 1

    # -1 0 50 100
    # -1 0 100 - [50,100] - will skip
    while i != len(mass_first) or j != len(mass_second):
        start = end
        quadric_1 = i - 1
        quadric_2 = j - 1

        if mass_first[i] < mass_second[j]:
            end = mass_first[i]
            i += 1
        elif mass_first[i] > mass_second[j]:
            end = mass_second[j]
            j += 1
        else:
            end = mass_second[j]
            j += 1
            i += 1

        if start - end == 0:
            continue
        ans += calculate(start, end,
                         [get_coord(triple_first, triple_second, quadric_1, quadric_2, 0),
                         get_coord(triple_first, triple_second, quadric_1, quadric_2, 1),
                         get_coord(triple_first, triple_second, quadric_1, quadric_2, 2)])
    print('%.6f' % float(ans))


if __name__ == '__main__':
    main()


"""
2 4
0 1 4
0 0 -1
0 0 0
0 1 3 4
0 0 0
0 0 -1
0 0 -1
0 0 -1
-> 4
"""