def read():
    graph = {}
    nodes = []
    with open("in1.txt", "r", encoding='utf-8') as f:
        lines = f.readlines()
        for line in lines:
            print(line)
            a = line.strip().split(' ') # A B C,  A B -1, A -1 C
            if graph.get(a[0]) is None:
                nodes.append(a[0])
            if graph.get(a[1]) is None and a[1] != -1:
                nodes.append(a[1])
            if graph.get(a[2]) is None and a[2] != -1:
                nodes.append(a[2])
            graph[a[0]] = (a[1], a[2])
    return graph, nodes


def inorder(node, graph, save):
    save.append(node)
    if graph.get(node) is not None:
        if graph[node][0] != "-1":
            inorder(graph[node][0], graph, save)
        if graph[node][1] != "-1":
            inorder(graph[node][1], graph, save)



def start_inorder(graph, nodes):
    print(nodes)
    print(graph)
    in_degree = {}
    for i in range(0, len(nodes)):
        print(nodes[i])
        in_degree[nodes[i]] = 0
    for key in graph:
        in_degree[graph[key][0]] += 1
        in_degree[graph[key][1]] += 1
    root = None
    for key in in_degree:
        if in_degree[key] == 0:
            root = key
            break
    save = []
    inorder(root, graph, save)
    save = "".join([save[i] for i in range(0, len(save))])
    print("save ", save)


graph, nodes = read()
print(graph)
print(nodes)
start_inorder(graph, nodes)








