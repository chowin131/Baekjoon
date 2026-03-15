import sys
def solve():
    n=int(sys.stdin.readline())
    if n==0 or n==1:
        print(n)
    else:
        a,b=0,1
        for i in range(2,n+1):
            a,b=b,a+b
        print(b)
solve()