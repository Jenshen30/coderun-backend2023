import os.path as p
import re


def getCanonicalNum(s: str):
	return "".join(list(filter(lambda x: x != '', re.split(r"[- \( \) +]", s))))


def isSubString(s1: str, s2: str):
	return p.commonprefix([s1, s2])


def telInfo(s):
	tel, info = s.split(" - ")
	diff = tel.count("X")
	tel = tel.replace("X", "")
	return tel, info, diff


def main():
	n = int(input())
	telBook = []

	for i in range(n):
		telBook.append(getCanonicalNum(input()))
	k = int(input())
	ans = ['' for i in range(n)]

	for i in range(k):
		s = str(input())
		manTel, info, diff = telInfo(s)
		for i in range(0, len(telBook)):
			tel = telBook[i]
			qq = isSubString(tel, getCanonicalNum(manTel))
			if len(qq) == len(getCanonicalNum(manTel)) and \
					len(getCanonicalNum(manTel)) + diff == len(tel):
				ans[i] = manTel + tel[len(qq):] + " - " + info
	print(*ans, sep="\n")



"""
4
28-49-5-123-45-67
87544456789
+28 (495) 123 45 56
875-(29)-123456
"""

if __name__ == '__main__':
	main()