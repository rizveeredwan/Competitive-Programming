
def valid(x,y):
    if x>=0 and x<=7 and y>=0 and y<=7:
        return True
    return False

def bfs(src, des):
    for i in range(0, 8):
        pass
    sx = src/8
    sy = src-8*sx
    dx = des/8
    dy = des-8*dx
    _list =[(sx,sy,0)]
    d = {}
    d[src] = 0
    i = 0
    mx = [2, 2, -2, -2,   1, -1, 1, -1]
    my = [1,-1, 1, -1,    2, 2, -2, -2 ]
    while True:
        cx,cy,cz = _list[i]
        if d.get(des) is not None:
            return d[des]
        for j in range(0, len(mx)):
            x = cx+mx[j]
            y = cy+my[j]
            if valid(x,y) is True and d.get(x*8+y) is None:
                d[x*8+y] = cz+1
                _list.append([x,y,cz+1])
        i = i + 1

#print(bfs(19, 36))
