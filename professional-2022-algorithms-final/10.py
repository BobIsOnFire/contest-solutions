import sys

def up(nums, last):
    if len(nums) == 1:
        return 1 if nums[0] > last else 0
    res = 0
    for i in nums:
        if i < last:
            continue
        copy = list(nums)
        copy.remove(i)
        res += down(copy, i)
    return res

def down(nums, last):
    if len(nums) == 1:
        return 1 if nums[0] < last else 0
    res = 0
    for i in nums:
        if i > last:
            continue
        copy = list(nums)
        copy.remove(i)
        res += up(copy, i)
    return res

print(up(range(1,int(sys.argv[1])+1), 0))