import sys

class MST_Kruskal:
    def __init__(self):
        self.edges = []
        self.N = None
        self.E = None 
        self.parent = []
        self.cost = 0 
        self.final_edge_set = []
    def find_parent(self, M):
        if self.parent[M] == M:
            return M 
        self.parent[M] = self.find_parent(self.parent[M])
        return self.parent[M] 
    def input_func(self):
        inp = input()
        inp = inp.split(' ')
        self.N = int(inp[0])
        self.E = int(inp[1])
        for i in range(0, self.N):
            inp = input()
            inp = inp.split(' ')
            a = int(inp[0])
            b = int(inp[1])
            c = int(inp[2])
            self.edges.append((a, b, c))
        self.edges.sort(key=lambda x: x[2])
    def rep_kruskal(self, flag_edges=None):
        self.parent = []
        for i in range(0, self.N+1):
            self.parent.append(i)
        cost = 0 
        final_set_of_edges = []
        for i in range(0, len(self.edges)):
            u = self.edges[i][0]
            v = self.edges[i][1]
            w = self.edges[i][2]
            if flag_edges is not None and flag_edges[i] == True:
                continue 
            p_u = self.find_parent(u)
            p_v = self.find_parent(v)
            if p_u != p_v:
                self.parent[p_u] = self.parent[p_v] 
                cost += w
                final_set_of_edges.append(i) 
            else: # already connected 
                continue 
        return cost, final_set_of_edges 

    def kruskal(self):
        for i in range(0, self.N+1):
            self.parent.append(i)
        for i in range(0, len(self.edges)):
            u = self.edges[i][0]
            v = self.edges[i][1]
            w = self.edges[i][2]
            p_u = self.find_parent(u)
            p_v = self.find_parent(v)
            if p_u != p_v:
                self.parent[p_u] = self.parent[p_v] 
                self.cost += w
                self.final_edge_set.append(i) 
            else: # already connected 
                continue 
        print(f"cost {self.cost}") 
        print("edges: ")
        for i in range(0, len(self.final_edge_set)):
            print(self.edges[self.final_edge_set[i]])
    
    def second_best(self):
        self.kruskal()
        flag_edges = []
        for i in range(0, len(self.edges)):
            flag_edges.append(False)
        second_cost = None 
        second_es = None 
        for i in range(0, len(self.final_edge_set)):
            flag_edges[self.final_edge_set[i]] = True 
            c, es = self.rep_kruskal(flag_edges=flag_edges)
            flag_edges[self.final_edge_set[i]] = False  
            print(f"{c} {es}")
            if second_cost is None:
                second_cost = c 
                second_es = es 
            elif second_cost > c:
                second_cost = c 
                second_es = es 
        print(f"{second_cost}")
        for i in range(0, len(second_es)):
            print(self.edges[second_es[i]])


file = open("in1.txt", "r")  # Open file manually
sys.stdin = file  # Redirect standard inputt

obj = MST_Kruskal()
obj.input_func()
#obj.kruskal()
obj.second_best()
