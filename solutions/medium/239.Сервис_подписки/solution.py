import json


def searchAllTrigAndShip(man, new_json, old_json):
    s = {}
    s["id"] = new_json["id"]
    for (k, v) in new_json.items():
        if k in man["triggers"] or k in man["shipments"]:
            s[k] = v

    for (k, v) in old_json.items():
        if k in man["shipments"] or k in man["triggers"]:
            if k not in s:
                 s[k] = v
            elif type(v) == dict:
                for (k2, v2) in v.items():
                    if k2 not in s[k]:
                        s[k][k2] = v2
    return s


def printtJson(man, new_json, old_json):
    ans = {}
    ans["trace_id"] = new_json["trace_id"]
    ans["offer"] = searchAllTrigAndShip(man, new_json["offer"], old_json)

    print(json.dumps(ans))


# json_string = json.dumps(data) - вывести на экран data json
def sendMessageForAllPeople(new_data, old, subs):
    for sub in subs:
        for (key, v) in new_data["offer"].items():
            if key in sub["triggers"]:
                if key in old and old[key] == v:
                    continue
                printtJson(sub, new_data, old)
                break


def checkEq(json_new, json_old):
    for (k, v) in json_new.items():
        if k == "id":
            continue
        if k not in json_old or json_old[k] != v:
            return False
    return True


def updateDatabase(new_data, database):
    id = new_data["id"]
    if id not in database:
        database[id] = {}

    for (k, v) in new_data.items():
        if k == "id":
            continue
        if k not in database[id] or database[id][k] != v:
            database[id][k] = v


def main():
    subscibers_num, q = map(int, input().split())
    subs = [{} for i in range(subscibers_num)]
    for i in range(subscibers_num):
        req = list(str(input()).split())
        triggers, shipments = int(req[0]), int(req[1])

        subs[i]["triggers"] = req[2:triggers + 2]
        subs[i]["shipments"] = \
            req[triggers + 2:triggers + 2 + shipments]

    database = {}

    for _ in range(q):
        data = json.loads(str(input()))

        if data["offer"]["id"] not in database:
            sendMessageForAllPeople(data, {}, subs)
            updateDatabase(data["offer"], database)
        elif not checkEq(data["offer"], database[data["offer"]["id"]]):
            sendMessageForAllPeople(data, database[data["offer"]["id"]], subs)
            updateDatabase(data["offer"], database)


if __name__ == '__main__':
    main()
"""
2 5
2 1 price stock_count lol1
1 2 partner_content lol1 lol2

2 1
2 0 price stock_count
1 0 stock_count
{"trace_id": "1", "offer": {"id": "1", "price": 9990, "stock_count": 100}}

2 2
2 0 price stock_count
1 0 stock_count
{"trace_id": "1", "offer": {"id": "1", "price": 9990, "stock_count": 100}}
{"trace_id": "2", "offer": {"id": "1", "price": 9990, "stock_count": 100}}



"""