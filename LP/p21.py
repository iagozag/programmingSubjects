def createCounter(n):
	t = {'x': n}
	t['inc'] = lambda: t.update({'x': t['x'] + 1})
	t['get'] = lambda: t['x']
	return t

o0 = createCounter(1)
o0['inc']()
print(o0['get']())

o1 = createCounter(100)
o1['inc']()
print(o1['get']())

o0['x'] += 1
print(o0['get']())

# 1.

class num:
	def __init__(self, _n):
		self.n = _n
	def inc(self):
		self.n += 1
	def get(self):
		return self.n


n = num(5)
print(n.get())
n.inc()
print(n.get())


# 2.
def square(n):
	return n*n

v = [1, 2, 3, 4, 5]
v = map(square, v)
print(list(v))
