num,length = map(int,input().split())
bas = list(map(int, input().split()))  
position,maxnum = bas[0]-length,1
lef,rig,cnt = 0,0,1
while rig < num-1 :
    while bas[rig]-bas[lef]<=length:
        rig +=1
        if rig == num:
            break
        cnt +=1
    rig -=1
    cnt -=1
    if cnt > maxnum:
        maxnum = cnt
        position = bas[rig]-length
    elif cnt == maxnum:
        position = min(bas[rig]-length,position)
    lef+=1
    cnt-=1
print(position, maxnum)   
      