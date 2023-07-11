import datetime


def checkInGroups(man, whoWhere, table, index):
	if table is []:
		return -1
	for group in table[index]:
		if man in whoWhere.get(group):
			return group
	return -1


def printt(table: list, whoWhere: dict, req: str):
	day, who = req.split()[1:3]

	i = int(day) * 24 * 60
	while i < (int(day) + 1) * 24 * 60:
		groupNum = checkInGroups(who, whoWhere, table, i)
		if groupNum > 0:
			startCur = i % (24 * 60)
			duration = 0
			while checkInGroups(who, whoWhere, table, i) == groupNum:
				duration += 1
				i += 1
			modify = datetime.time(startCur // 60, startCur % 60)
			print(modify.strftime('%H:%M'), duration, *whoWhere.get(checkInGroups(who, whoWhere, table, i - 1)))
		else:
			i += 1


def checkIsEmpty(table: list, start, duration, people: list, whoWhere):
	ans = [0 for i in range(len(people))]
	for i in range(start, start + duration):
		if table[i] is not []:
			for m in range(0, len(people)):
				man = people[m]
				for groupId in table[i]:
					if man in whoWhere.get(groupId):
						ans[m] = 1
	return ans


def setPeple(table: list, start, duration, id):
	for i in range(start, start + duration):
		table[i].append(id)


def repeats(time, table: list, people: list, whoWhere):
	ans = []
	for groupId in table[time]:
		tmp = whoWhere.get(groupId)
		for man in people:
			if man in tmp:
				ans.append(man)
	return ans


def appoint(id: int, table: list, whoWhere: dict, req: str):
	day, starttime, duration, num_people = req.split()[1:5]

	duration = int(duration)
	starttime = int(day) * 24 * 60 + int(starttime.split(":")[0]) * 60 + int(starttime.split(":")[1])
	people = list(req.split()[5:5+int(num_people)])
	res = checkIsEmpty(table, starttime, duration, people, whoWhere)
	if sum(res) == 0:
		setPeple(table, starttime, duration, id)
		whoWhere[id] = people
		print("OK")
	else:
		print("FAIL")
		for i in range(0, len(res)):
			if res[i] == 1:
				print(people[i], end=" ")
		print()


def main():
	n = int(input())

	global_timetable = [[] for i in range((365 + 1) * 24 * 60)]
	booked = {}
	for i in range(1, n + 1):
		request = str(input())
		if request.startswith("APPOINT"):
			appoint(i, global_timetable, booked, request)
		else:
			printt(global_timetable, booked, request)


if __name__ == '__main__':
	main()
"""
7
APPOINT 1 12:30 30 2 andrey alex
APPOINT 1 12:00 30 2 alex sergey
APPOINT 1 12:59 60 2 alex andrey
PRINT 1 alex
PRINT 1 andrey
PRINT 1 sergey
PRINT 2 alex

4
APPOINT 2 08:00 120 3 alex lol kir
APPOINT 2 8:00 15 3 lol kir ab
APPOINT 1 21:59 120 1 alex
PRINT 2 alex



APPOINT 1 21:59 120 10 andrey alex andrey1 andrey2 alex2 alex3 alex4 alex9 alex8 alex10
APPOINT 1 21:44 15 10 andrey alex andrey1 andrey2 alex2 alex3 alex4 alex9 alex8 alex10

"""
