from fractions import Fraction


def integrate(t, m):
    a = t[0]
    if len(t) == 1:
        return (3 * a * m ** 2 - 2 * m ** 3) / (6 * a)

    b = t[1]
    if len(t) == 2:
        return (6 * a * b * m ** 2 -\
                4 * a * m ** 3 -\
                4 * b * m ** 3 +\
                3 * m ** 4) / (12 * a * b)

    c = t[2]
    if len(t) == 3:
        return (30 * a * b * c * m ** 2 -\
                20 * a * b * m ** 3 -\
                20 * a * c * m ** 3 -\
                20 * b * c * m ** 3 +\
                15 * a * m ** 4 +\
                15 * b * m ** 4 +\
                15 * c * m ** 4 -\
                12 * m ** 5) / (60 * a * b * c)
    d = t[3]
    if len(t) == 4:
        return 1 / (60 * a * b * c * d) * m ** 2 *\
               (-12 * m ** 3 * (a + b + c + d) +\
                15 * m ** 2 * (a * (b + c + d) + b * (c + d) + c * d) -\
                20 * m * (a * d * (b + c) + a * b * c +\
                          b * c * d) + 30 * a * b * c * d + 10 * m ** 4)


if __name__ == '__main__':
    n = int(input())

    t_s = list(map(Fraction, input().split()))
    t_min = min(t_s)

    if n == 1:
        ans = t_min / 2
        print(str(ans.numerator) + "/" + str(ans.denominator))
    else:
        res = Fraction(0)
        for i in range(0, n):
            new_mass = []
            for j in range(0, n):
                if j != i:
                    new_mass.append(t_s[j])

            res += integrate(new_mass, t_min) / Fraction(t_s[i])
        print(str(res.numerator) + "/" + str(res.denominator))

"""
1
1 2 3 4 5
2 3 5 7 11

50
50 50 50 50 50
50 49 48 47 46
50 49 47 43 41

"""