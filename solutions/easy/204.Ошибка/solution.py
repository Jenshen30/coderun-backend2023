def main():
	n = int(input())
	ans = []
	modus = 0
	for i in range(n):
		p1, n1 = map(int, input().split())
		modus += (p1 * n1)
		ans.append(p1 * n1)
	ans = list(map(lambda x: x / modus, ans))
	print(*ans, end="\n")


if __name__ == '__main__':
	main()