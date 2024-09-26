num,length = map(int,input().split())
bas = list(map(int, input().split()))  
position,maxnum = bas[0]-length,1

lef,rig,cnt = 0,0,1
while rig < num-1 :
    flag = False
    while bas[rig]-bas[lef]<=length:
        rig +=1
        cnt +=1
        flag = True
    if flag:
        rig -=1
        cnt -=1
    while bas[rig]-bas[lef]>length:
        lef +=1
        cnt -=1
    if cnt > maxnum:
        maxnum = cnt
        position = bas[rig]-length
    if cnt == maxnum:
        if (bas[rig]-length)<position:
            position = bas[rig]-length
    rig+=1
    cnt+=1
print(position, maxnum)   
    