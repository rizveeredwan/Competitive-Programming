def floyd_warshall(matrix):
    distance = []
    for i in range(0, len(matrix)):
        distance.append([])
        for j in range(0, len(matrix)):
            distance[i].append(matrix[i][j])
    for k in range(0, len(matrix)):
        for i in range(0, len(matrix)):
            for j in range(0, len(matrix)):
                if distance[i][j] > (distance[i][k] + distance[k][j]):
                    distance[i][j] = distance[i][k] + distance[k][j]
    neg_cycle = False
    for k in range(0, len(matrix)):
        for i in range(0, len(matrix)):
            for j in range(0, len(matrix)):
                if distance[i][j] > (distance[i][k] + distance[k][j]):
                    distance[i][j] = distance[i][k] + distance[k][j]
                    neg_cycle = True
                    break
            if neg_cycle is True:
                break
        if neg_cycle is True:
            break
    return distance, neg_cycle


def gen(ml, bunny_cnt, curr_list, full_list, flags):
    if len(curr_list) == ml:
        full_list.append([])
        for i in range(0, len(curr_list)):
            full_list[-1].append(curr_list[i])
        return
    for i in range(1, bunny_cnt+1):
        if flags[i] == 0:
            flags[i] = 1
            curr_list.append(i)
            gen(ml, bunny_cnt, curr_list, full_list, flags)
            curr_list.pop()
            flags[i] = 0
    return


def calc(_list, distance):
    curr_node = 0
    t = 0
    for i in range(0, len(_list)):
        t += distance[curr_node][_list[i]]
        curr_node = _list[i]
    t += distance[curr_node][len(distance)-1]
    return t


def solution(times, time_limit):
    distance, neg_cycle = floyd_warshall(times)
    res = []
    if neg_cycle is True:
        for i in range(1, len(times)-1):
            res.append(i-1)
    else:
        full_list = []
        bunny_cnt = len(times)-2
        flag = {}
        for i in range(1, bunny_cnt+1):
            flag[i] = 0
        for i in range(1, bunny_cnt+1):
            gen(ml=i, bunny_cnt=bunny_cnt, curr_list=[], full_list=full_list, flags=flag)
        for i in range(len(full_list)-1, -1, -1):
            t = calc(full_list[i], distance)
            if t <= time_limit:
                if len(res) > len(full_list[i]):
                    break
                if len(res) < len(full_list[i]):
                    full_list[i].sort()
                    res = []
                    for j in range(0, len(full_list[i])):
                        res.append(full_list[i][j]-1)
                elif len(res) == len(full_list[i]):
                    full_list[i].sort()
                    update = False
                    for j in range(0, len(full_list[i])):
                        if (full_list[i][j]-1) < res[j]:
                            update = True
                            break
                    if update is True:
                        res = []
                        for j in range(0, len(full_list[i])):
                            res.append(full_list[i][j] - 1)
    # print(res)
    return res


#print(solution([[0, 1, 1, 1, 1], [1, 0, 1, 1, 1], [1, 1, 0, 1, 1], [1, 1, 1, 0, 1], [1, 1, 1, 1, 0]], 3))
#print(solution([[0, 2, 2, 2, -1], [9, 0, 2, 2, -1], [9, 3, 0, 2, -1], [9, 3, 2, 0, -1], [9, 3, 2, 2, 0]], 1))
