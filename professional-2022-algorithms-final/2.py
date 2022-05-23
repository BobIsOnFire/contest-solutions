first_left = 0
second_left = 0
queue = 0

for time in range(1000):
    if time % 5 == 0:
        queue += 1
    
    work = first_left > 0 and second_left > 0
    if work:
        first_left -= 0.5
        second_left -= 0.5
    elif first_left > 0:
        first_left -= 1
    elif second_left > 0:
        second_left -= 1
    
    if queue > 0:
        if first_left == 0:
            first_left = 6
            queue -= 1
        elif second_left == 0:
            second_left = 6
            queue -= 1
    
    print(time, first_left, second_left, queue)

