def main():
	t = int(input())
	for i in range(t):
		n = int(input())
		l = list(map(int, input().split()))

		ac = max(l) + 10 ** 9
		l.sort()
		for i in range(0, len(l) - 1):
			ac = min(ac, l[i] ^ l[i + 1])
		print(ac)


if __name__ == '__main__':
	main()
"""
1 January 2015
31 December 2015
"""