def main():
	s = str(input())
	s = s + "A"
	setik = set(list(input()))

	for lenchik in range(1, len(s) + 1):
		for j in range(0, len(s) + 1):
			if lenchik + j >= len(s):
				break
			ans = True
			tmp = set()
			for k in range(j, j + lenchik):
				if s[k] not in setik:
					ans = False
				tmp.add(s[k])
			if ans and len(setik) == len(tmp):
				print(lenchik)
				return
	print(0)


if __name__ == '__main__':
	main()