best_value = 0

def recursion(i, sum, dp, _list):
    if i<0:
        if(sum%3 == 0):
            return 0
        else:
            return -10000000000000000000
    if dp.get(i) is not None and dp[i].get(sum) is not None:
        return dp[i][sum]
    res1 = recursion(i-1, (sum+_list[i])%3, dp, _list)+1  # %3
    res2 = recursion(i-1, sum, dp, _list)
    if dp.get(i) is None:
        dp[i]={}
    if dp[i].get(sum) is None:
        dp[i][sum] = 0
    dp[i][sum] = max(res1, res2)
    return dp[i][sum]

def generation(i, sum, dp, _list, gens):
    global best_value
    #print(dp[i][sum], gens)
    if (i==0):
        # print("dhuki")
        if dp[i][sum] == 1:
            gens.append(_list[i])
            generation(i-1, (sum+_list[i])%3, dp, _list, gens) # %3
            gens.pop()
        else:
            generation(i-1, sum, dp, _list, gens)
        return
    if i<0:
        # print(gens)
        temp = []
        for j in range(0, len(gens)):
            temp.append(gens[j])
        temp.sort(reverse=True)
        calc = 0
        for j in range(0, len(temp)):
            calc = calc*10 + temp[j]
        if calc > best_value:
            best_value = calc
        return
    if ( (i-1)>= 0 and dp[i][sum] == dp[i-1][(sum+_list[i])%3] + 1): # %3
        gens.append(_list[i])
        generation(i-1, (sum+_list[i])%3, dp, _list, gens) # %3
        gens.pop()
    if((i-1)>=0 and dp[i][sum] == dp[i-1][sum]):
        generation(i-1, sum, dp, _list, gens)
    return

def all_zero(l):
    flag = None
    for i in range(0, len(l)):
        if l[i] == 0:
            flag=True
            continue
        else:
            flag = False
            break
    return flag

def solution(l):
    # print(_list, type(_list), len(_list))
    if (all_zero(l) == True):
        _string = ""
        for i in range(0, len(l)):
            _string = _string+str(l[i])
        return _string

    _list = l
    global best_value
    dp={}
    res = recursion(len(_list)-1, 0, dp, _list)
    # print(res)
    best_value = 0
    gens = []
    generation(len(_list)-1, 0, dp, _list, gens)
    return best_value

def digits(number):
    _list = []
    while(number>0):
        _list.append(number%10)
        number = int(number/10)
    return _list

#print(solution([3, 1,  5, 9, 4, 1]))
for i in range(1, 1000000000):
    if(i%3 == 0):
        _list = digits(i)
        print(_list)
        ans = solution(_list)
        assert(ans !=0)
        print("done")

# print(solution([0,0]))
