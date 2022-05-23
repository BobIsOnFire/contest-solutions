waiting = False
block = False
block_release = 0
queue = 0
exec = list()

max_queue = 0

for i in range(1000000):
    if i % 3 == 0:
        queue += 1

    if i < block_release:
        if queue > max_queue:
            max_queue = queue
        # print(f"{i} {sorted(exec)} {queue} {'WAITING ' if waiting else ''}{'BLOCKED ' if block else ''}{block_release}")
        continue
    else:
        if not waiting:
            block = False

    if i % 20 == 0 and i > 0:
        waiting = True

    while i in exec:
        exec.remove(i)
    
    if len(exec) == 0 and waiting:
        block = True
        waiting = False
        block_release = i + 10

    if not waiting and not block:
        while queue > 0 and len(exec) < 5:
            exec.append(i + 7)
            queue -= 1

    if queue > max_queue:
        max_queue = queue

    # print(f"{i} {sorted(exec)} {queue} {'WAITING ' if waiting else ''}{'BLOCKED ' if block else ''}{block_release}")

print(max_queue)