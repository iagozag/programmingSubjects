import time

def sievePrimes0(candidates):
    """Removes every non-prime number from the ordered list l."""
    candidates = list(candidates)  # Convert range to a list to allow item assignment
    for i in range(0, int(len(candidates) ** 0.5 + 1)):
        currentPrime = candidates[i]
        if currentPrime != 0:
            for j in range(i + currentPrime, len(candidates), currentPrime):
                if candidates[j] % currentPrime == 0:
                    candidates[j] = 0
    return list(filter(lambda x: x != 0, candidates))  # Convert filter to list to view primes

def sievePrimes1(l):
    """Removes every non-prime number from the ordered list l."""
    l = list(l)  # Convert filter object to a list to enable indexing and slicing
    if l[0] * l[0] <= l[len(l) - 1]:
        l[1:] = sievePrimes1(filter(lambda x: x % l[0] != 0, l))
    return l

def timeSieve(maxPrime, numTimes, sieveFunc):
	"""Times the sieve implementations."""
	t0 = 0
	for numTries in range(0, numTimes):
		taux = time.perf_counter()
		primes0 = sieveFunc(range(2, maxPrime))
		t0 = t0 + time.perf_counter() - taux
	print (t0 / numTimes)

def pydiv(n, d):
	return n/d if d != 0 else None

def perm(n, l):
	ans = []
	def aux(has, vis):
		if len(has) == n:
			ans.append(has[:])
			return

		for i in range(0, len(l)):
			if not vis[i]:
				has.append(l[i])
				vis[i] = True
				aux(has, vis)
				has.pop()
				vis[i] = False

	aux([], [False for i in range(len(l))]	)
	return ans

def prime_perm():
	pm = sorted(perm(4, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]))
	primes = []
	for p in pm:
		np = int("".join(map(str, p)))
		for m in range(2, np):
			if np%m == 0:
				break
		else:
			primes.append(p)
	pm = primes
	for i in range(0, len(pm)):
		for j in range(i+1, len(pm)):
			for k in range(j+1, len(pm)):
				if sorted(pm[i]) == sorted(pm[j]) and sorted(pm[j]) == sorted(pm[k]):
					a = int("".join(map(str, pm[i])))
					b = int("".join(map(str, pm[j])))
					c = int("".join(map(str, pm[k])))
					if b-a == c-b:
						print(pm[i], pm[j], pm[k])

