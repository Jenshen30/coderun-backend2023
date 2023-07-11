def solver(n):
	tmp = int(n ** 0.5) + 1
	c = 0
	for d in range(2, tmp + 1):
		if n % d == 0:
			c += 1
		while n % d == 0:
			n //= d
	# if n - prime
	if n > 1:
		c += 1
	return c


def main():
	gcd, lcm = map(int, input().split())
	# common rule
	if lcm % gcd != 0:
		return print(0)
	# all combinations to put divisors of lcm // gcd in p or q
	return print(2 ** solver(lcm // gcd))


if __name__ == '__main__':
	main()
