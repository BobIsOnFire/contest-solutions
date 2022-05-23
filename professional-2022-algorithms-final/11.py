from math import floor, sqrt


for a in range(-6, 0) + range(1, 7):
    for b in range(-6, 0) + range(1, 7):
        for c in range(-6, 0) + range(1, 7):
            D = b**2 - 4 * a * c
            if D <= 0:
                continue
            sq = floor(sqrt(D))
            if sq**2 == D and (b + sq) % (2 * a) == 0 and (b - sq) % (2 * a) == 0:
                print(a, b, c)

