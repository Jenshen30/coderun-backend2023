def main():
	n = int(input())
	l = list(map(int, input().split()))
	m = dict()
	for el in l:
		if el not in m.keys():
			m[el] = 0
		m[el] = m.get(el) + 1

	maxiNumber, maxiFrec = -1, -1

	for (num, frec) in m.items():
		if frec > maxiFrec:
			maxiNumber, maxiFrec = num, frec
		elif frec == maxiFrec and num > maxiNumber:
			maxiNumber, maxiFrec = num, frec
	print(maxiNumber)


if __name__ == '__main__':
	main()