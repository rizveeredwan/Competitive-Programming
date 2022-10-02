def gcd(a, b):
    if a == 0:
        return b
    if b == 0:
        return a
    return gcd(b, a % b)


def lcm(a, b):
    if a == 0 or b == 0:
        return 1
    return (a/ gcd(a, b))* b

def fraction_normalize(lob, hor):
    if hor == 0 or lob == 0:
        hor = 1
    g = gcd(abs(lob), abs(hor))
    lob /= g
    hor /= g
    if lob < 0 and hor < 0:
        lob *= -1
        hor *= -1
    elif lob > 0 and hor < 0:
        lob *= -1
        hor *= -1
    return lob, hor


def sum_frac(lob1, hor1, lob2, hor2):
    hor_base = lcm(hor1, hor2)
    lob_base = (hor_base / hor1) * lob1 + (hor_base / hor2) * lob2
    lob_base, hor_base = fraction_normalize(lob_base, hor_base)
    return lob_base, hor_base


def gaussian_elimination(_list):
    for i in range(0, len(_list)):
        id = i
        for j in range(i + 1, len(_list)):  # in each row
            #value1 = (_list[j][i][0] / _list[j][i][1])  # lob/hor
            #value2 = (_list[id][i][0] / _list[id][i][1])  # lob/hor
            if abs(_list[j][i][0] *  _list[id][i][1]) > abs(_list[id][i][0] * _list[j][i][1]): #(l1/h1) > (l2/h2) => (l1 * h2) > (l2 * h1)
                id = j
        if id != i:
            # swapping
            #print("id = ",id, _list[id][i])
            for j in range(0, len(_list[i])):  # included B here
                #print("i j",i,j)
                temp_lob, temp_hor = _list[i][j][0], _list[i][j][1]
                _list[i][j][0], _list[i][j][1] = _list[id][j][0], _list[id][j][1]
                _list[id][j][0], _list[id][j][1] = temp_lob, temp_hor

        # run elimination
        for j in range(0, len(_list)):
            if i != j:
                b_lob, b_hor = _list[j][i][0], _list[j][i][1]
                if b_lob == 0:
                    continue
                a_lob, a_hor = _list[i][i][0], _list[i][i][1]
                lob = a_lob * b_hor
                hor = a_hor * b_lob
                lob, hor = fraction_normalize(lob, hor)
                if lob == 0:
                    continue
                if hor == 0:
                    hor = 1
                for k in range(0, len(_list[j])):
                    _list[j][k][0], _list[j][k][1] = _list[j][k][0] * (lob), _list[j][k][1] * hor
                    _list[j][k][0], _list[j][k][1] = fraction_normalize(_list[j][k][0], _list[j][k][1])
                    _list[j][k][0], _list[j][k][1] = sum_frac(_list[j][k][0], _list[j][k][1], -1*_list[i][k][0],
                                                              _list[i][k][1])

    # print(_list)
    for i in range(0, len(_list)):
        _list[i][-1][0] *= _list[i][i][1]
        _list[i][-1][1] *= _list[i][i][0]
        _list[i][-1][0], _list[i][-1][1] = fraction_normalize(_list[i][-1][0], _list[i][-1][1])
        # print(_list[i][-1][0], _list[i][-1][1])
        _list[i][i][0] = 1
        _list[i][i][1] = 1
        # input()
    # print(_list)
    return _list


def identifying_terminals(_list):
    idx = []
    for i in range(0, len(_list)):
        all_zero = True
        for j in range(0, len(_list[i])):
            if _list[i][j] > 0:
                all_zero = False
                break
        if all_zero is True:
            idx.append(i)
    return idx


def id_non_terminal(_list, terminals):
    cnt = 0
    non_terminal = []
    i = 0
    while i<len(_list):
        if cnt < len(terminals) and terminals[cnt] > i:
            non_terminal.append(i)
            i = i + 1
        elif cnt < len(terminals) and terminals[cnt] == i:
            i = i + 1
            cnt += 1
        elif cnt>=len(terminals):
            non_terminal.append(i)
            i = i+1
    return non_terminal


def create_list_for_gauss(s, terminal_id, norms, non_terminal):
    base_list = []
    for i in range(0, len(s)):
        if i in non_terminal or i == terminal_id:
            _list = []
            for j in range(0, len(s[i])):
                if j in non_terminal or j == terminal_id:
                    prob = [-s[i][j], norms[i]]
                    if j == i:
                        prob[0], prob[1] = sum_frac(lob1=1, hor1=1, lob2=prob[0], hor2=prob[1])
                    prob[0], prob[1] = fraction_normalize(prob[0], prob[1])
                    _list.append(prob)
            if i in non_terminal:
                _list.append([0, 1])
            elif i == terminal_id:
                _list.append([1,1])
            base_list.append(_list)
    return base_list


def zero_solution(s, terminals, ans):
    for i in range(0, len(terminals)):
        tt = terminals[i]
        possible = False
        for j in range(0, len(s)):
            if s[j][tt] > 0:
                possible = True
                break
        if possible is False:
            ans[i] = [0, 1]


def calculate_hor_for_prob(s):
    norms = []
    for i in range(0, len(s)):
        _sum = 0
        for j in range(0, len(s[i])):
            _sum += s[i][j]
        if _sum == 0:
            _sum = 1
        norms.append(_sum)
    return norms


def solution(s):
    terminals = identifying_terminals(s)
    ans = []
    for i in range(0, len(terminals)):
        ans.append(None)
    non_terminals = id_non_terminal(s, terminals)
    # zero_solution(s, terminals, ans)
    # print(ans)
    norms = calculate_hor_for_prob(s)
    # print(norms)
    for i in range(0, len(terminals)):
        if ans[i] is None:
            terminal_id = terminals[i]
            base_list = create_list_for_gauss(s=s, terminal_id=terminal_id, norms=norms, non_terminal=non_terminals)
            # print(base_list)
            base_list = gaussian_elimination(base_list)
            ans[i] = [int(base_list[0][-1][0]), int(base_list[0][-1][1])]
            # print("calculation ",base_list)
    l = ans[0][1]
    # print(ans)
    for i in range(1, len(terminals)):
        l = int(lcm(l, ans[i][1]))
    save = []
    for i in range(0, len(ans)):
        a = l/ans[i][1]
        a = ans[i][0]*a
        save.append(int(a))
    save.append(l)
    # print(save)
    return save


# print(gcd(12, 6))
_list = [
    [[2, 1], [-1, 1], [3, 1], [15, 1]],
    [[4, 1], [-2, 1], [2, 1], [42, 1]],
    [[1, 1], [1, 1], [-1, 1], [9, 1]]
]

# gaussian_elimination(_list)

_list = [[0, 1, 0, 0, 0, 1],
         [4, 0, 0, 3, 2, 0],
         [0, 0, 0, 0, 0, 0],
         [0, 0, 0, 0, 0, 0],
         [0, 0, 0, 0, 0, 0],
         [0, 0, 0, 0, 0, 0]]

#_list = [[0, 2, 1, 0, 0], [0, 0, 0, 3, 4], [0, 0, 0, 0, 0], [0, 0, 0, 0,0], [0, 0, 0, 0, 0]]
#_list = [[0, 1, 1], [0, 0, 0], [0, 0, 0]]
#_list = [[1, 1, 1], [1, 1, 1], [0, 0, 0]]

# https://codeforces.com/blog/entry/60003 

#print(solution(_list))
