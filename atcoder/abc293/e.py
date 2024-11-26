import time
import bisect
import functools
import math
import os
import random
import re
import sys
import threading
from collections import Counter, defaultdict, deque
from copy import deepcopy
from functools import cmp_to_key, lru_cache, reduce
from heapq import heapify, heappop, heappush, heappushpop, nlargest, nsmallest
from io import BytesIO, IOBase
from itertools import accumulate, combinations, permutations
from operator import add, iand, ior, itemgetter, mul, xor
from string import ascii_lowercase, ascii_uppercase
from typing import *

BUFSIZE = 4096
class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)

class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")

sys.stdin = IOWrapper(sys.stdin)
sys.stdout = IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")

def I():
    return input()

def II():
    return int(input())

def MII():
    return map(int, input().split())

def LI():
    return list(input().split())

def LII():
    return list(map(int, input().split()))

def GMI():
    return map(lambda x: int(x) - 1, input().split())

def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))

inf = float('inf')

# class Factorial:
#     def __init__(self, N, mod) -> None:
#         N += 1
#         self.mod = mod
#         self.f = [1 for _ in range(N)]
#         self.g = [1 for _ in range(N)]
#         for i in range(1, N):
#             self.f[i] = self.f[i - 1] * i % self.mod
#         self.g[-1] = pow(self.f[-1], mod - 2, mod)
#         for i in range(N - 2, -1, -1):
#             self.g[i] = self.g[i + 1] * (i + 1) % self.mod

#     def fac(self, n):
#         return self.f[n]

#     def fac_inv(self, n):
#         return self.g[n]

#     def comb(self, n, m):
#         if n < m or m < 0:
#             return 0
#         return self.f[n] * self.g[m] % self.mod * self.g[n - m] % self.mod

#     def perm(self, n, m):
#         return self.f[n] * self.g[n - m] % self.mod

#     def catalan(self, n):
#         return (self.comb(2 * n, n) - self.comb(2 * n, n - 1)) % self.mod

#     def inv(self, n):
#         return self.f[n-1] * self.g[n] % mod

"""
template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}
"""

def inve(a, m):
    u=0,v=1
    while a!=0:
        t=m//a
        m-=t*a
        a,m=m,a
        u-=t*v
        u,v=v,u
    return u

a,x,m=MII()

if(a==1):
    ans=x%m
    print(ans)
else:
    

# mod = 998244353
# fac = Factorial(10 ** 6 + 1, mod)
# pt = PrimeTable(10 ** 6 + 1)

# n = II()
# nums = LII()
# cnt = Counter(sorted(nums))
# dp = [0] * (n + 1)
# dp[0] = 1

# acc = 0
# for num in cnt:
#     if not pt.is_prime(num):
#         for i in range(n+1):
#             dp[i] = dp[i] * fac.comb(n - (acc - i), cnt[num]) % mod
#     else:
#         new_dp = [0] * (n + 1)
#         for i in range(n+1):
#             new_dp[i] += dp[i] * fac.comb(n - (acc - i), cnt[num]) % mod
#         for i in range(1, n+1):
#             new_dp[i] += dp[i-1] * fac.comb(n - (acc - i + 1), cnt[num] - 1) % mod
#             new_dp[i] %= mod
#         dp = new_dp
#     acc += cnt[num]
# print(dp[-1])