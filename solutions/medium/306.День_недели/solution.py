import datetime
import sys


def main():
	lines = sys.stdin.readlines()
	for line in lines:
		if line == "":
			return
		d, mont, y = line.split()

		monthCodes = {
			"January": 1,
			"October": 10,
			"May": 5,
			"August": 8,
			"February": 2,
			"March": 3,
			"November": 11,
			"June": 6,
			"December": 12,
			"September": 9,
			"April": 4,
			"July": 7}

		m = {
			1: "Monday",
			2: "Tuesday",
			3: "Wednesday",
			4: "Thursday",
			5: "Friday",
			6: "Saturday",
			0: "Sunday"
		}

		day = datetime.datetime(int(y), monthCodes.get(mont), int(d))
		print(m.get((day.weekday() + 1) % 7))


if __name__ == '__main__':
	main()
"""
1 January 2015
31 December 2015


"""