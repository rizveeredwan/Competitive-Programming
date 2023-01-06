import sys
import functools


def sort(a, b):
    if a[1] < b[1]: # least value possible
        return -1
    if a[1] == b[1]:
        if a[2] > b[2]: # enforces more constraint
            return -1
        else:
            return 1
    return 1


class MapColor:
    def __init__(self):
        self.number_of_colors = None
        self.edge = None
        self.node = None
        self.graph = {}
        self.all_colored = False
        self.best_coding = []

    def input_graph(self):
        line = input().strip().split(' ')
        self.node = int(line[0])
        self.edge = int(line[1])
        for i in range(0, self.node):
            self.graph[i] = []
        for i in range(0, self.edge):
            s = input()
            s = s.strip().split(' ')
            s[0], s[1] = int(s[0]), int(s[1])
            self.graph[s[0]-1].append(s[1]-1)
            self.graph[s[1]-1].append(s[0]-1)
        self.number_of_colors = int(input())
        # print(self.number_of_colors)

    def forward_table_check(self, forward_table):
        for i in range(0, self.node):
            not_none = True
            for j in range(0, self.number_of_colors):
                if forward_table[i][j] is None:
                    not_none = False
                else:
                    not_none = True
                    break
            if not_none is False:
                return True # problem
        return False # No problem

    def H1(self, forward_table, i):
        cnt = 0
        for j in range(0, self.number_of_colors):
            if forward_table[i][j] is not None:
                cnt += 1
        return cnt

    def H2(self, i, current_color_coding):
        cnt = 0
        for j in range(0, len(self.graph[i])):
            u = self.graph[i][j]
            if current_color_coding[u] is None: # not colored this neighbour, will enforce condition
                cnt += 1
        return cnt

    def backtrack(self, current_color_coding=[], colord=0, forward_table=[]):
        print(current_color_coding)
        if colord == self.node:
            # print(current_color_coding)
            for i in range(0, self.node):
                self.best_coding[i] = current_color_coding[i]
            self.all_colored = True
            return
        # forward table is empty
        verdict = self.forward_table_check(forward_table)
        if verdict is True: # problem detected
            return
        options = []
        for i in range(0, self.node):
            if current_color_coding[i] is None:
                options.append([i, self.H1(forward_table, i),
                                self.H2(i, current_color_coding)]) # ith node can be colord, H1, H2, H3 values

        options.sort(key=functools.cmp_to_key(sort))
        #print(options)
        for i in range(0, len(options)):
            node = options[i][0]
            for j in range(0, self.number_of_colors):
                if forward_table[node][j] is not None: # this color can be picked
                    current_color_coding[node] = j # choosing the color
                    updates = []
                    for k in range(0, len(self.graph[node])):
                        u = self.graph[node][k]
                        if forward_table[u][j] is True:
                            forward_table[u][j] = None
                            updates.append(u)
                    self.backtrack(current_color_coding, colord+1, forward_table)
                    if self.all_colored is True:
                        return
                        # pass
                    # reverting back
                    current_color_coding[node] = None
                    for k in range(0, len(updates)):
                        u = updates[k]
                        forward_table[u][j] = True

    def algorithm(self):
        forward_table = []
        print(self.node)
        for i in range(0, self.node):
            forward_table.append([])
            self.best_coding.append(None)
            for j in range(0, self.number_of_colors):
                forward_table[i].append(True)
        #print(forward_table)
        current_color_coding = []
        for i in range(0, self.node):
            current_color_coding.append(None)
        #print(current_color_coding)
        self.all_colored = False
        self.backtrack(current_color_coding, 0, forward_table)
        if self.all_colored is True:
            for i in range(0, self.node):
                print(self.best_coding[i])
        else:
            print("NO")


if __name__  == '__main__':
    sys.stdin = open("in1.txt", "r")
    obj = MapColor()
    obj.input_graph()
    obj.algorithm()
