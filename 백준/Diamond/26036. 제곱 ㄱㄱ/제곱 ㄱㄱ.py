import sys
n=int(sys.stdin.read())
x,y=3,1
t=100**n
while 8*y*y<t:x,y=3*x+8*y,x+3*y
sys.stdout.write(f"{y} 2\n{x} 1")