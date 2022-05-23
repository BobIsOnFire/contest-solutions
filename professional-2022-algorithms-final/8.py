for i in range(32):
    print(i, 3 ** i, 3 ** i <= 100000)

for i in range(32):
    print(i, 2 ** i, 2 ** i <= 100000)

n = 1
for i in range(1, 21):
    n *= i
print(n)
print(2 ** 20)
