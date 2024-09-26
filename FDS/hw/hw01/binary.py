def count_nums(array,pos):
    left= 0
    right = len(array)-1
    while left < right:
        mi =( left + right)//2
        if array[mi] >= pos:
            right = mi
        else:
            left = mi+1
    return left
num,length = map(int,input().split())
bas = list(map(int, input().split()))    
position,maxnum = bas[0]-length,1
for p in range(num):
    pos = bas[p]-length
    left = count_nums(bas,pos)
    count = p - left +1
    if count > maxnum:
        maxnum = count
        position = bas[p]-length
    if count == maxnum:
        if (bas[p]-length)<position:
            position = bas[p]-length
print(position, maxnum)
    
    