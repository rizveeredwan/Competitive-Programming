def solution(x,y):
    M = x
    F = y
    itr = 0
    M = int(M)
    F = int(F)
    while True:
        #print(M,F)
        if (M==1 and F==1):
            return str(itr)
        if (M<=0) or (F<=0):
            return "impossible"
        if M>=F:
            if (M%F == 0):
                val = int(M/F)-1
            else:
                val = int(M/F)
            M=M-F*val
            itr = itr+ val
        elif M<F:
            if (F%M == 0):
                val = int(F/M)-1
            else:
                val = int(F/M)
            F=F-M*val
            itr = itr+ val
    # return str(itr)

#print(solution('7', '4'))
