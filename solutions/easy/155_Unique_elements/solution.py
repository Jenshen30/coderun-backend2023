def main():
	n = int(input())
	l = list(map(int, input().split()))

	s = dict()
	ans = 0
	for el in l:
		if el not in s.keys():
			s[el] = 0

		s[el] = s.get(el) + 1

	for el in s.values():
		if el == 1:
			ans += 1

	print(ans)


if __name__ == '__main__':
	main()