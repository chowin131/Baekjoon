import sys
input=sys.stdin.readline
def ccw(a,b,c):return(b[0]-a[0])*(c[1]-a[1])-(b[1]-a[1])*(c[0]-a[0])<0
while True:
 n=int(input())
 if not n:break
 P=sorted([(*map(int,input().split()),i)for i in range(n)])
 M=[0]*n;C=1
 while len(P)>=3:
  m=len(P);L=[];U=[]
  for j in P:
   while len(L)>1 and ccw(L[-2],L[-1],j):L.pop()
   L.append(j)
  for j in P[::-1]:
   while len(U)>1 and ccw(U[-2],U[-1],j):U.pop()
   U.append(j)
  for j in L+U:M[j[2]]=C
  P=[j for j in P if M[j[2]]!=C]
  C+=1
 print("Take this onion to the lab!"if C%2==0 else"Do not take this onion to the lab!")