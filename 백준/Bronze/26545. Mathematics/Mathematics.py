import sys
input = sys.stdin.read().split()
n = int(input[0])
numbers = map(int, input[1:])
print(sum(numbers))