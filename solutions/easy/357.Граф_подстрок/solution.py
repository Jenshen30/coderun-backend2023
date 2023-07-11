def main():
	n = int(input())
	words = set()
	for _ in range(n):
		words.add(str(input()))

	graph = {}
	vertexes = 0
	edges = 0
	for word in words:
		for start in range(0, len(word) - 2):
			if word[start:start+3] not in graph:
				vertexes += 1
				graph[word[start:start + 3]] = dict()
			if start != 0:
				if word[start:start+3] not in graph.get(word[start-1:start+2]):
					edges += 1
					graph.get(word[start-1:start+2])[word[start:start+3]] = 0
				graph.get(word[start - 1:start + 2])[word[start:start + 3]] += 1

	print(vertexes)
	print(edges)
	for (v1, others) in graph.items():
		for (v2, value) in others.items():
			print(v1, v2, value)


if __name__ == '__main__':
	main()
"""
10 60 1
0 100 0 1 120 121 60 0 0 0

3 0 1
0 0 0
"""
