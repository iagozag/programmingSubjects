class mySet:
	v = []
	ordered = []

	def __init__(self):
		self.v = [None]*100000
	
	def find(self, n):
		i = 0;
		while True:
			if n == self.v[i]:
				return True
			elif self.v[i] == None:
				return False
			elif n < self.v[i]:
				i = i*2+1
			else:
				i = i*2+2
		return False

	def add(self, n):
		i = 0;
		while True:
			if n == self.v[i]:
				break
			elif self.v[i] == None:
				self.v[i] = n
				self.ordered.append(n)
				break
			elif n < self.v[i]:
				i = i*2+1
			else:
				i = i*2+2
	
	def __str__(self):
		self.ordered.sort()
		result = "{"+", ".join(str(x) for x in self.ordered)+"}"
		return result


ms = mySet()

ms.add(1)
ms.add(4)
print(ms.find(3))
ms.add(3)
print(ms.find(1))
print(ms.find(2))
print(ms.find(3))
print(ms.__str__())
