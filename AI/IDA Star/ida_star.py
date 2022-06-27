import sys

class IDA_Star:
    def __init__(self):
        self.graph = {}
        self.heuristic = {}
        self.INF = 1000000000
        self.start, self.goal = None, None
        self.path = []
        self.best_result = self.INF

    def input_func(self):
        l = input()
        l = l.strip().split(' ')
        n = int(l[0])
        edge = int(l[1])
        for i in range(edge):
            l = input()
            l = l.strip().split(' ')
            a = l[0]
            b = l[1]
            c = int(l[2])
            if self.graph.get(a) is None:
                self.graph[a] = {}
            if self.graph.get(b) is None:
                self.graph[b] = {}
            self.graph[a][b] = c
            self.graph[b][a] = c
            self.heuristic[a] = self.INF
        for i in range(n):
            l = input()
            l = l.strip().split(' ')
            a = l[0]
            b = int(l[1])
            self.heuristic[a] = b
        self.start = input()
        self.goal = input()
        self.path.clear()

    def search(self, n, cost, f):
        # print("path ", self.path)
        if cost + self.heuristic[n] > f:
            print(self.path, cost + self.heuristic[n])
            return cost + self.heuristic[n]  # threshold failure
        if n == self.goal:
            print(self.path)
            self.best_result = cost
            return True  # goal reached
        updated_f = self.INF
        found = False
        for v in self.graph[n]:
            self.path.append([v, cost + self.graph[n][v], self.heuristic[v], cost + self.graph[n][v]+self.heuristic[v]])
            found = self.search(v, cost + self.graph[n][v], f)
            if found is True:
                return True
            updated_f = min(updated_f, found)
            self.path.pop()
        return updated_f

    def ida_star(self):
        f = 0
        while True:
            # print(self.start, self.goal)
            self.path = [self.start]
            found = self.search(self.start, 0, f)
            if found is True:
                break
            f = found
            print("iteration done")
            print(f)
        print(self.path, self.best_result)


if __name__ == '__main__':
    # equivalent to freopen
    sys.stdin = open("in1.txt", "r")
    obj = IDA_Star()
    obj.input_func()
    obj.ida_star()






