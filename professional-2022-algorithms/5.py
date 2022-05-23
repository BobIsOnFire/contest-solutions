line = input()

one = 1
two = 1

sum = 0

for i in range(len(line)-1,-1,-1):
    print(i, line[i])
    if line[i] == '1':
        sum += two
    (one, two) = (two, one + two)

print(sum)