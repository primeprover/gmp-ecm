# First run
# sage --preparse check_gpuecm.sage
# mv check_gpuecm.sage.py check_gpuecm.py

import check_gpuecm

import gmpy2

prime_start = 10 ** 8 + 1
primes = [p for p in range(prime_start, prime_start + 10 ** 5, 2) if gmpy2.is_prime(p)]
print("Testing", len(primes), "primes")

# Want
# 0: a*b
# 1: a*c*d
# 2: None
# 3: b*c
# 4: e

curves = 8
sigma = 1000
B1 = 1000

average_sigma = 0
matches = [None, None, None, None, None]
for p in primes:
    s1 = check_gpuecm.smallGroupOrders(p, check_gpuecm.GPU_PARAM, sigma, B1, curves)
    s1 = tuple(s - sigma for s in s1)
    average_sigma += len(s1)
    if s1 == (0, 1):
        matches[0] = p
    elif s1 == (0, 3):
        matches[1] = p
    elif s1 == (1, 3):
        matches[2] = p
    elif s1 == (1,):
        matches[3] = p
    elif s1 == (4,):
        matches[4] = p

    if all(matches):
        print(matches)
        print('echo "%s" | ./ecm -gpu -gpucurves %d -sigma %d:%d %d 0' % (
            "*".join(map(str,matches)), curves, check_gpuecm.GPU_PARAM, sigma, B1))
        break
else:
    print(matches)
    print("Didn't find match, increment sigma or increase prime range")
    print("Sigma/prime: %.2f" % (average_sigma / len(primes)))
