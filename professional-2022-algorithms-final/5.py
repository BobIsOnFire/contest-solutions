def fun():
    for i in range(100):
        if 19 * i % 22 == 1:
            return i

print(fun())

# А Б В Г Д Е Ж З  И  Й  К  Л  М  Н  О  П  Р  С  Т  У  Ф  Х  Ц  Ч  Ш  Щ  Ы  Ь  Э  Ю  Я
# 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32

for c in [5, 12, 16, 26]:
    print((c ** 7) % 46)
