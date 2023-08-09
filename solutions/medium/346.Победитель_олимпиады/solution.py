import requests


def doRec(url: str):
    response = requests.get("http://127.0.0.1:7777" + url)
    return response.text


def clear(xml, keyWord):
    return xml.replace("<?xml version=\"1.0\" encoding=\"UTF-8\"?>", "")\
            .replace("<" + keyWord + "s>", "")\
            .replace("<" + keyWord, "")\
            .replace("/>", "")\
            .replace("</" + keyWord + "s>", "")


def parseStatistics(xml):
    statistic = dict()
    cleared = clear(xml, "submission")
    for triple in [cleared.split()[start::3] for start in range(3)]:
        for i in range(len(triple)):
            var, value = triple[i].replace("\"", "").split("=")
            if i not in statistic:
                statistic[i] = dict()
            statistic[i][var] = value

    ans = {}
    for (k, v) in statistic.items():
        if v["problem"] not in ans:
            ans[v["problem"]] = []
        ans[v["problem"]].append((int(v["timestamp"]), v["verdict"]))

    for (k, v) in ans.items():
        ans[k].sort(key=lambda p: p[0])

    return ans


def parseParticipants(xml):
    ans = set()
    cleared = clear(xml, "participant")
    for el in cleared.split():
        t = el.split("=")
        ans.add(t[1].replace("\"", ""))
    return ans


# fixme binsearch
def searchFirstOK(attempts):
    for i in range(len(attempts)):
        attempt = attempts[i]
        if attempt[1] == "OK":
            return i
    return -1


def getScore(man_stat: dict):
    #    tasks  penalty
    score = [0, 0]
    for (task, attempts) in man_stat.items():
        firstOK = searchFirstOK(attempts)
        if firstOK == -1:
            continue
        score_tmp = 0
        for attempt in attempts[0:firstOK + 1]:
            if attempt[1] == "CE":
                continue
            if attempt[1] == "OK":
                score[0] += 1

                score[1] += attempt[0] + score_tmp * 20
            else:
                score_tmp += 1
    return score


def get_all_names(contest_name: str):
    # dict with no data
    participants = parseParticipants(doRec("/view/participants?contest=" + contest_name))
    scores = {}
    max_tasks = 0
    for participant in participants:
        scores[participant] =\
        getScore(parseStatistics(doRec("/view/submissions?contest=" + contest_name + "&login=" + participant)))
        max_tasks = max(scores[participant][0], max_tasks)

    min_penalty = 10 ** 20

    for (man, score) in scores.items():
        if score[0] == max_tasks:
            min_penalty = min(score[1], min_penalty)

    ans = []

    for (man, score) in scores.items():
        if score[0] == max_tasks and score[1] == min_penalty:
            ans.append(man)
    print(len(ans))
    return sorted(ans)


def main():
    contest_name = str(input())

    print(*get_all_names(contest_name), sep="\n")


if __name__ == '__main__':
    main()