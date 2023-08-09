def main():
	n = int(input())
	blacklist = set()
	for _ in range(n):
		blacklist.add(str(input()))
	m = int(input())
	info = {}
	for _ in range(m):
		s = str(input())
		for black in blacklist:
			info[s] = False
			if s.startswith(black):
				info[s] = True
				break

	k = int(input())
	for _ in range(k):
		q = str(input())
		stat = {}
		for (name, isBad) in info.items():
			if name.startswith(q) and isBad:
				tmp = "." + name.split("/")[-1].split(".")[-1]
				if tmp not in stat:
					stat[tmp] = 0
				stat[tmp] += 1
		print(len(stat.keys()))
		for item, amount in stat.items():
			print("{}: {}".format(item, amount))


if __name__ == '__main__':
	main()
"""
10 60 1
0 100 0 1 120 121 60 0 0 0

3 0 1
0 0 0
"""
