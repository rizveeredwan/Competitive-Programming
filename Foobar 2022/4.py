def solution(l):
    # Your code here
    info={}
    count={}
    for i in range(len(l)-1, -1, -1):
        info[i]=[]
        for j in range(i-1, -1, -1):
            #print("i, j ",i,j,l[i]%l[j])
            if (l[j]>0 and l[i]%l[j] == 0):
                info[i].append(j)
    for i in range(0, len(l)):
        count[i] = len(info[i])
        # print(i, count[i])
    ans = 0
    for i in range(len(l)-1, -1, -1):
        for j in range(0, len(info[i])):
            #print(i, j, info[i][j], count[info[i][j]])
            ans += count[info[i][j]]
    return ans

# print(solution([1, 2, 3, 4, 5, 6]))
