from collections import deque
import sys


def dls(m, n, sx, sy, gx, gy, maze, level_threshold):
    visited = {}
    dx = [1, 0, 0, -1]
    dy = [0, 1, -1, 0]
    stack = deque([])
    stack.append([sx, sy, 0, maze[sx][sy], 0, None, None]) # cellx, celly, level, cost, index in path, parentx, parenty
    paths = [(sx, sy, None)]
    visited[sx] = {}
    visited[sx][sy] = True
    while len(stack) > 0:
        u = stack.popleft()
        # print(u)
        if u[0] == gx and u[1] == gy:
            return u[3], paths, u[4]
        for i in range(0, len(dx)):
            x = u[0] + dx[i]
            y = u[1] + dy[i]
            if 0 <= x < m and 0 <= y < n and (u[2]+1 <= level_threshold) and maze[x][y] != -1:
                if visited.get(x) is not None and visited[x].get(y) is not None:
                    continue
                if visited.get(x) is None:
                    visited[x] = {}
                if visited[x].get(y) is None:
                    visited[x][y] = True
                paths.append((x, y, u[4]))  # parent in which index
                stack.append([x, y, u[2]+1, u[3]+maze[x][y], len(paths)-1, u[0], u[1]])
    return None, None, None


def dfs_with_rec(i, j, m, n, visited, maze, gx, gy, level, level_threshold, parent_info):
    if i == gx and j == gy:
        return maze[i][j]
    if level > level_threshold:
        return None
    dx = [1, 0, 0, -1]
    dy = [0, 1, -1, 0]
    for x in range(0, len(dx)):
        nx = i + dx[x]
        ny = j + dy[x]
        if 0 <= nx < m and 0 <= ny < n:
            if visited.get(nx) is not None and visited[nx].get(ny) is not None:
                continue
            if maze[nx][ny] == -1:
                continue
            if visited.get(nx) is None:
                visited[nx] = {}
                parent_info[nx] = {}
            if visited[nx].get(ny) is None:
                visited[nx][ny] = True
                parent_info[nx][ny] = (i, j)
            cost = dfs_with_rec(nx, ny, m=m, n=n, visited=visited, maze=maze, gx=gx, gy=gy, level=level+1,
                                level_threshold=level_threshold, parent_info=parent_info)
            if cost is not None:
                return cost + maze[i][j]
    return None


def print_path(parent_info, gx, gy, sx, sy, maze):
    s = 0
    save = []
    while True:
        save.append((gx, gy))
        s += maze[gx][gy]
        if gx == sx and gy == sy:
            break
        gx, gy = parent_info[gx][gy]
    print(len(save))
    for i in range(len(save)-1, -1, -1):
        print(save[i][0], save[i][1])
    # print("sum ", s)


def ids_with_rec(m, n, sx, sy, gx, gy, maze):
    for level_threshold in range(0, 5001):
        visited = {}
        parent_info = {}
        cost = dfs_with_rec(i=sx, j=sy, m=m, n=n, visited=visited, maze=maze, gx=gx, gy=gy, level=0,
                            level_threshold=level_threshold, parent_info=parent_info)
        # print(level_threshold, cost)
        if cost is not None:
            print(f"{cost}")
            print_path(parent_info=parent_info, sx=sx, sy=sy, gx=gx, gy=gy, maze=maze)
            return cost
    return None


def ids(m, n, sx, sy, gx, gy, maze):
    level_threshold = 0
    cost = -1
    paths = None
    end = None
    while True:
        cost, paths, end = dls(m=m, n=n, sx=sx, sy=sy, gx=gx, gy=gy, maze=maze, level_threshold=level_threshold)
        # print(cost, level_threshold)
        if cost is None:
            level_threshold += 1
        else:
            # print(f"{cost}, {level_threshold}")
            return cost, paths, end
        if level_threshold > 5000:
            return cost, paths, end


def extract_path(paths, idx, maze):
    save = []
    while idx is not None:
        save.append([paths[idx][0], paths[idx][1]])
        idx = paths[idx][2]
    print(len(save))
    _sum = 0
    for i in range(len(save)-1, -1, -1):
        print(save[i][0], save[i][1], maze[save[i][0]][save[i][1]])
        _sum += maze[save[i][0]][save[i][1]]
    print("sum ",_sum)


sys.setrecursionlimit(100000000)


def DP(i, j, cost, sx, sy, dp, maze, m, n, tracked):
    # print("came ", i, j, cost)
    # input()
    if i == sx and j == sy:
        if cost-maze[i][j] == 0:
            print("YEAH ",cost, maze[i][j])
            if dp.get(i) is None:
                dp[i] = {}
            if dp[i].get(j) is None:
                dp[i][j] = {}
            dp[i][j][cost] = True
            return True
        return False
    if i<0 or j<0 or cost<0 or i>=m or j>=n:
        # print("OH NO")
        return False
    if dp.get(i) is not None and dp[i].get(j) is not None and dp[i][j].get(cost) is not None:
        # print("DHUKSI ",i,j,cost)
        return dp[i][j][cost]
    dx = [1, 0, 0, -1]
    dy = [0, 1, -1, 0]
    res = False
    if tracked.get(i) is None:
        tracked[i] = {}
    if tracked[i].get(j) is None:
        tracked[i][j] = {}
    if tracked[i][j].get(cost) is None:
        tracked[i][j][cost] = True
        # print("saving ", i, j, cost)
    for x in range(0, len(dx)):
        nx = i+dx[x]
        ny = j+dy[x]
        # print("what ", i, j, cost, nx, ny)
        if 0 <= nx < m and 0 <= ny < n:
            if maze[nx][ny] == -1:
                continue
            if tracked.get(nx) is not None and tracked[nx].get(ny) is not None and tracked[nx][ny].get(cost-maze[i][j]) is not None:
                continue
            res = res | DP(i=nx, j=ny, cost=cost-maze[i][j], sx=sx, sy=sy, dp=dp, maze=maze, m=m, n=n, tracked=tracked)
            if res is True:
                # print(i, j, nx, ny, cost, cost-maze[i][j], maze[i][j])
                break
    if dp.get(i) is None:
        dp[i] = {}
    if dp[i].get(j) is None:
        dp[i][j] = {}
    if dp[i][j].get(cost) is None:
        dp[i][j][cost] = False
    dp[i][j][cost] = res
    return res


def get_path_from_dp(i, j, cost, dp, maze, m, n, save, sx, sy, tracked):
    save.append((i, j, cost, maze[i][j]))
    print(i, j, cost)
    dx = [1, 0, 0, -1]
    dy = [0, 1, -1, 0]
    if i == sx and j == sy and (cost-maze[i][j]) == 0:
        print(save)
        return
    if tracked.get(i) is None:
        tracked[i] = {}
    if tracked[i].get(j) is None:
        tracked[i][j] = {}
    if tracked[i][j].get(cost) is None:
        tracked[i][j][cost] = True
    if i <0 or i>=m or j < 0 or j >= n or cost<0:
        # print("WTF")
        return
    for x in range(0, len(dx)):
        nx = i + dx[x]
        ny = j + dy[x]
        # print("what ", i, j, cost, nx, ny, dp[i][j][cost])
        if 0 <= nx < m and 0 <= ny < n:
            if maze[nx][ny] == -1:
                continue
            # print("ASE ", maze[nx][ny])
            if dp.get(nx) is not None and dp[nx].get(ny) is not None and dp[nx][ny].get(cost - maze[i][j]) is not None and \
                    dp[nx][ny][cost - maze[i][j]] is True:
                #
                if tracked.get(nx) is not None and tracked[nx].get(ny) is not None and tracked[nx][ny].get(
                        cost - maze[i][j]) is not None:
                    continue
                print("possible ", nx, ny, cost - maze[i][j])
                get_path_from_dp(nx, ny, cost - maze[i][j], dp, maze,  m, n, save, sx, sy, tracked)
                save.pop()
    return save


def solution():
    sys.stdin = open("in5.txt", "r")
    sys.stdout = open("out5.txt", "w")
    l = input().strip().split(' ')
    m, n = int(l[0]), int(l[1])
    maze = []
    for i in range(0, m):
        maze.append([])
        l = input().strip().split(' ')
        for j in range(len(l)):
            l[j] = int(l[j])
        maze[i] = l
    l = input().split(' ')
    sx, sy, gx, gy = int(l[0]), int(l[1]), int(l[2]), int(l[3])
    """
    cost, paths, end = ids(m=m, n=n, sx=sx, sy=sy, gx=gx, gy=gy, maze=maze)
    if cost is not None:
        print(cost)
        if cost != -1:
            extract_path(paths, end, maze)
    else:
        print("-1")
    """
    cost = ids_with_rec(m=m, n=n, sx=sx, sy=sy, gx=gx, gy=gy, maze=maze)
    if cost is None:
        print("-1")
    """
    dp = {}
    tracked = {}
    res = DP(gx, gy, 55, sx, sy, dp, maze, m, n, tracked)
    if res is True:
        print(res)
        get_path_from_dp(gx, gy, 55, dp, maze, m, n, [], sx, sy,{})
    """


if __name__ == '__main__':
    solution()