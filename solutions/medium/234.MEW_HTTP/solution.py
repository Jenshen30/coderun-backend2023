import requests


def doRec(param1, param2, reqs, param3=""):

    params = {
        "X-Cat-Variable": param1 + ", " + param2 + ", " * int(len(param3) > 0) + param3
    }

    # forth var first
    response = requests.request("MEW", "http://127.0.0.1:7777/", headers=params)
    reqs.append(response.headers.get("x-cAt-VAlue").split(", "))
    return response.headers.get("x-cAt-VAlue").split(", ")


def addToFrec(l: list, frec):
    for el in l:
        if el not in frec:
            frec[el] = 0
        frec[el] += 1


def pickNotIt(l, val):
    c = 0
    for el in l:
        if el != val or c > 0:
            return el
        c += 1


def main():
    var_names = []
    for i in range(4):
        var_names.append(str(input()))

    reqs = []
    frec = {}
    ans = {}

    addToFrec(doRec(var_names[0], var_names[1], reqs, var_names[2]), frec)
    addToFrec(doRec(var_names[1], var_names[3], reqs), frec)
    addToFrec(doRec(var_names[2], var_names[3], reqs), frec)

    # ones
    for (k, v) in frec.items():
        if v % 2 == 1:
            ans[var_names[0]] = k
    reqs[0].remove(ans[var_names[0]])

    # doubled
    if len(set(reqs[1])) < 2:
        ans[var_names[3]] = reqs[1][0]
        ans[var_names[1]] = reqs[1][0]
        ans[var_names[2]] = pickNotIt(reqs[0], ans[var_names[1]])
    elif len(set(reqs[2])) < 2:
        ans[var_names[3]] = reqs[2][0]
        ans[var_names[2]] = reqs[2][0]
        ans[var_names[1]] = pickNotIt(reqs[1], ans[var_names[2]])
    elif len(set(reqs[0])) < 2:
        ans[var_names[2]] = reqs[0][0]
        ans[var_names[1]] = reqs[0][0]
        ans[var_names[3]] = pickNotIt(reqs[2], ans[var_names[1]])
    else:
        ans[var_names[1]] = list(set(reqs[0]).intersection(set(reqs[1])))[0]
        ans[var_names[2]] = pickNotIt(reqs[0], ans[var_names[1]])
        ans[var_names[3]] = pickNotIt(reqs[1], ans[var_names[1]])

    for el in var_names:
        print(ans[el])


if __name__ == '__main__':
    main()