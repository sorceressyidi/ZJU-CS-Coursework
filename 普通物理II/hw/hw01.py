import math
def U1_odd(x):
    sum = 0.0
    cita = 2.0*math.pi/x
    for i in range(1,(x+1)//2):
        sum += 1/math.sin(i*cita/2)
    res = x*sum/2
    return res
def U1_even(x):
    sum = 0.0
    cita = 2.0*math.pi/x
    for i in range(1,(x//2)):
        sum += 1/math.sin(i*cita/2)
    sum  +=0.5
    res = x*sum/2
    return res
def U2_odd(x):
    sum = 0.0
    cita = 2.0*math.pi/(x-1)
    for i in range(1,(x-1)//2):
        sum += 1/math.sin(i*cita/2)
    sum += 2.5
    res = (x-1)*sum/2
    return res
def U2_even(x):
    sum = 0.0
    cita = 2.0*math.pi/(x-1)
    for i in range(1,x//2):
        sum += 1/math.sin(i*cita/2)
    sum += 2
    res = (x-1)*sum/2
    return res
for i in range(5,15):
    if i % 2==0 :
        print(U1_even(i))
        print(U2_even(i))
        print("######")
    else:
        print(U1_odd(i))
        print(U2_odd(i))
    