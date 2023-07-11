def main():
	s1 = set(list(input()))
	s2 = str(input())
	ans = 0
	for i in s2:
		if i in s1:
			ans += 1

	print(ans)


if __name__ == '__main__':
	main()
"""
5
6 26 126



"""