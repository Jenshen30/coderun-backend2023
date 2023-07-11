def main():
	k, m, d = map(int, input().split())

	ans = 0
	hungry = 0

	# calc first week
	for i in range(d, 8):
		if i != 6 and i != 7:
			m += k
		m -= i - d + 1
		if m < 0:
			print(ans)
			return
		hungry = i - d + 1
		ans += 1

	# starting from Monday
	# weeks
	left, right = 0, 10 ** 30
	while right - left > 1:
		mid = (left + right) // 2
		# hungry hungry + 1 .. hungry + mid * 7
		if (m + mid * k * 5) - ((mid * 7) * (2 * (hungry) + 1 + mid * 7) // 2) >= 0:
			left = mid
		else:
			right = mid

	# calc last week
	m = m + left * k * 5 - ((left * 7) * (2 * (hungry) + 1 + left * 7) // 2)
	for day in range(1, 8):
		if day != 6 and day != 7:
			m += k
		m -= left * 7 + day + hungry
		if m < 0:
			print(ans + left * 7)
			return
		ans += 1


if __name__ == '__main__':
	main()
