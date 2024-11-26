standard_input, packages, output_together = 1, 1, 0
dfs, hashing, read_from_file = 1, 0, 0
de = 1

if 1:

    if standard_input:
        import io, os, sys
        input = lambda: sys.stdin.readline().strip()

        import math
        inf = math.inf

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

        def LFI():
            return list(map(float, input().split()))

        def GMI():
            return map(lambda x: int(x) - 1, input().split())

        def LGMI():
            return list(map(lambda x: int(x) - 1, input().split()))

    if packages:
        from io import BytesIO, IOBase

        import random
        import os

        import bisect
        import typing
        from collections import Counter, defaultdict, deque
        from copy import deepcopy
        from functools import cmp_to_key, reduce, lru_cache
        from heapq import merge, heapify, heappop, heappush, heappushpop, nlargest, nsmallest
        from itertools import accumulate, combinations, permutations, count, product
        from operator import add, iand, ior, itemgetter, mul, xor
        from string import ascii_lowercase, ascii_uppercase, ascii_letters
        from typing import *
        BUFSIZE = 4096

    if output_together:
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

        sys.stdout = IOWrapper(sys.stdout)

    if dfs:
        from types import GeneratorType

        def bootstrap(f, stack=[]):
            def wrappedfunc(*args, **kwargs):
                if stack:
                    return f(*args, **kwargs)
                else:
                    to = f(*args, **kwargs)
                    while True:
                        if type(to) is GeneratorType:
                            stack.append(to)
                            to = next(to)
                        else:
                            stack.pop()
                            if not stack:
                                break
                            to = stack[-1].send(to)
                    return to
            return wrappedfunc

    if hashing:
        RANDOM = random.getrandbits(20)
        class Wrapper(int):
            def __init__(self, x):
                int.__init__(x)

            def __hash__(self):
                return super(Wrapper, self).__hash__() ^ RANDOM

    if read_from_file:
        file = open("input.txt", "r").readline().strip()[1:-1]
        fin = open(file, 'r')
        input = lambda: fin.readline().strip()
        output_file = open("output.txt", "w")
        def fprint(*args, **kwargs):
            print(*args, **kwargs, file=output_file)

    if de:
        def debug(*args, **kwargs):
            print('\033[92m', end='')
            print(*args, **kwargs)
            print('\033[0m', end='')

def sa_naive(s):
    n = len(s)
    return sorted(range(n), key=lambda i: s[i:])

def sa_doubling(s):
    def key(i):
        if i + k < n:
            return rank[i], rank[i + k]
        return rank[i], -1

    smax = max(s) + 1
    n = len(s)
    sa = list(range(n))
    rank = s[:]
    tmp = [0] * n

    k = 1
    while k < n:
        sa.sort(key=key)
        tmp[sa[0]] = 0
        for i in range(1, n):
            tmp[sa[i]] = tmp[sa[i-1]] + (key(sa[i-1]) < key(sa[i]))
        rank, tmp = tmp, rank
        k <<= 1
    return sa

def sa_is(s, upper, THRESHHOLD_NAIVE=20, THRESHHOLD_DOUBLE=100):
    def induce(lms):
        for i in range(n):
            sa[i] = -1
        buf = sum_s[:]
        for d in lms:
            if d == n:
                continue
            sa[buf[s[d]]] = d
            buf[s[d]] += 1

        buf = sum_l[:]
        sa[buf[s[n - 1]]] = n - 1
        buf[s[n - 1]] += 1
        for i in range(n):
            v = sa[i]
            if v >= 1 and not ls[v - 1]:
                sa[buf[s[v - 1]]] = v - 1
                buf[s[v - 1]] += 1

        buf = sum_l[:]
        for i in range(n)[::-1]:
            v = sa[i]
            if v >= 1 and ls[v - 1]:
                buf[s[v - 1] + 1] -= 1
                sa[buf[s[v - 1] + 1]] = v - 1

    n = len(s)
    if n == 0:
        return []
    if n == 1:
        return [0]
    if n <= THRESHHOLD_NAIVE:
        return sa_naive(s)
    if n <= THRESHHOLD_DOUBLE:
        return sa_doubling(s)

    sa = [0] * n
    ls = [0] * n
    for i in range(n - 1)[::-1]:
        if s[i] == s[i + 1]:
            ls[i] = ls[i + 1]
        else:
            ls[i] = int(s[i] < s[i + 1])

    sum_l = [0] * (upper + 1)
    sum_s = [0] * (upper + 1)
    for i, x in enumerate(ls):
        if not x:
            sum_s[s[i]] += 1
        else:
            sum_l[s[i] + 1] += 1
    for i in range(upper + 1):
        sum_s[i] += sum_l[i]
        if i < upper:
            sum_l[i + 1] += sum_s[i]

    lms_map = [-1] * (n + 1)
    lms = []
    m = 0
    for i in range(1, n):
        if not ls[i - 1] and ls[i]:
            lms_map[i] = m
            lms.append(i)
            m += 1

    induce(lms)

    if m:
        sorted_lms = []
        for v in sa:
            if v == -1:
                print("minuse")
            if lms_map[v] != -1:
                sorted_lms.append(v)

        rec_s = [0] * m
        rec_upper = 0
        rec_s[lms_map[sorted_lms[0]]] = 0
        for i in range(1, m):
            l = sorted_lms[i - 1]
            r = sorted_lms[i]
            end_l = lms[lms_map[l] + 1] if lms_map[l] + 1 < m else n
            end_r = lms[lms_map[r] + 1] if lms_map[r] + 1 < m else n
            same = 1
            if end_l - l != end_r - r:
                same = 0
            else:
                while l < end_l:
                    if s[l] != s[r]:
                        break
                    l += 1
                    r += 1
                if l == n or s[l] != s[r]:
                    same = 0
            if not same:
                rec_upper += 1
            rec_s[lms_map[sorted_lms[i]]] = rec_upper

        rec_sa = sa_is(rec_s, rec_upper)
        for i in range(m):
            sorted_lms[i] = lms[rec_sa[i]]
        induce(sorted_lms)
    return sa

def suffix_array(S, compress=True):
    if compress:
        ch = sorted(set(S))
        ctoi = {c: i for i, c in enumerate(ch, 1)}
        S = [ctoi[s] for s in S]

    upper = max(S) + 1
    return sa_is(S, upper)

def construct_lcp(s, sa):
    n = len(s)
    assert(n >= 1)
    rank = [0] * n
    for i in range(n):
        rank[sa[i]] = i

    lcp = [0] * n
    h = 0
    for i in range(n):
        if h > 0:
            h -= 1
        if rank[i] == 0:
            continue
        j = sa[rank[i] - 1]
        while j + h < n and i + h < n:
            if s[j + h] != s[i + h]:
                break
            h += 1
        lcp[rank[i] - 1] = h
    return lcp

t = II()
outs = []

for _ in range(t):
    n, left, right = MII()
    s = I()
    
    ans = [0] * (n + 1)
    
    sa = suffix_array(s)
    lcp = construct_lcp(s, sa)
    
    idx = sa.index(0)
    tmp = [0] * n
    tmp[0] = n
    
    for i in range(idx - 1, -1, -1):
        tmp[sa[i]] = min(tmp[sa[i+1]], lcp[i])
    
    for i in range(idx, n-1):
        tmp[sa[i+1]] = min(tmp[sa[i]], lcp[i])
    
    bound = 100
    for length in range(1, n // bound + 1):
        cur = -n - 1
        cnt = 0
        for i in range(n):
            if tmp[i] >= length and i - cur >= length:
                cnt += 1
                cur = i
        ans[cnt] = length
    
    for i in range(n - 1, -1, -1):
        ans[i] = max(ans[i], ans[i+1])
    
    for k in range(1, min(bound, n) + 1):
        l, r = 1, n // k
        while l <= r:
            m = (l + r) // 2
            cur = -n - 1
            cnt = 0
            for i in range(n):
                if tmp[i] >= m and i - cur >= m:
                    cnt += 1
                    cur = i
            if cnt >= k: l = m + 1
            else: r = m - 1
        ans[k] = r
    
    outs.append(' '.join(map(str, ans[left:right+1])))

print('\n'.join(outs))