import sys
import math
def solve():
    input=sys.stdin.buffer.read().split()
    T=int(input[0])
    idx=0
    results=[]
    for i in range(T):
        xA=int(input[idx+1])
        yA=int(input[idx+2])
        xC=int(input[idx+3])
        yC=int(input[idx+4])
        v=int(input[idx+5])
        idx+=5
        d=math.hypot(xA-xC,yA-yC)
        if v<=1:
            results.append("-1")
            continue
        k=math.sqrt(v*v-1)
        A1=0.0
        dtheta=math.pi/10000
        for i in range(10000):
            theta=-math.pi/2+(i+0.5)*dtheta
            ct=math.cos(theta)
            r=d*(-ct+math.sqrt(ct*ct+k*k))/(k*k)
            A1+=r*r*dtheta/2.0
        A2=d*d/(2*k)*(math.exp(math.pi/k)-1)
        results.append(f"{A1+A2:.8f}")
    print('\n'.join(results))
solve()