class Solution:
    def beautifulSubsets(self, a: List[int], k: int) -> int:
        n=len(a)
        m=(1<<n)
        p = [0 for i in range(1001)]
        c=0
        for i in range(1,m):
            o=1
            for j in range(n):
                if i &(1<<j):
                    p[a[j]]=1
                    if a[j]-k>1 and p[a[j]-k]>0:
                        o=0
                        break
                    if a[j]+k<=1000 and p[a[j]+k]>0:
                        o=0
                        break
            if o:
                c += 1
        return c
