
class TreeNode:
    def __init__(self, id=-1, depth=0):
        self.id = id
        self.merge_info = {}
        self.own_info = []
        self.child = {}
        self.depth = depth
        self.parent_node = None

    def update(self, own_info):
        self.own_info = own_info
        merge_info = {}


def generate_tree(global_list):
    tree_dict = TreeNode()
    ref_list = {}
    for i in range(0, len(global_list)):
        curr = tree_dict
        # print(global_list[i])
        for j in range(0, len(global_list[i])):
            if curr.child.get(global_list[i][j]) is None:
                curr.child[global_list[i][j]] = TreeNode(id=global_list[i][j], depth=j+1)
                curr.child[global_list[i][j]].parent_node = curr
                if ref_list.get(global_list[i][j]) is None:
                    ref_list[global_list[i][j]] = []
                ref_list[global_list[i][j]].append(curr.child[global_list[i][j]])
            curr = curr.child[global_list[i][j]]
    return tree_dict, ref_list


def verify_union_v2(id, global_list, ref_list, max_number, max_depth):
    for i in range(0, len(ref_list[id])):
        ref_list[id][i].own_info = global_list[id]
        merge_info = {}
        cnt = 0
        parent_info = {}
        if ref_list[id][i].parent_node is not None:
            parent_info = ref_list[id][i].parent_node.merge_info
        for key in parent_info:
            merge_info[key] = True
            cnt += 1
        if cnt >= (max_number+1):
            if (ref_list[id][i].depth-1) < max_depth: # problem: ended in parent
                return False
        for j in range(0, len(global_list[id])):
            if merge_info.get(global_list[id][j]) is None:
                merge_info[global_list[id][j]] = True
                cnt += 1
        ref_list[id][i].merge_info = merge_info
        if cnt >= (max_number+1):
            if ref_list[id][i].depth < max_depth: # problem: have child ended here
                return False
        if ref_list[id][i].depth == max_depth:
            if cnt != (max_number+1):
                return False
    return True


def generation(k, st, en, local_list, global_list):
    # print(k, st, en, local_list, global_list)
    if len(local_list) == k:
        global_list.append([])
        for i in range(0, len(local_list)):
            global_list[-1].append(local_list[i])
        return
    for i in range(st, en+1):
        local_list.append(i)
        generation(k, i+1, en, local_list, global_list)
        local_list.pop()
    return


def verify(final_list, global_list, max_number):
    #print(global_list)
    #print(final_list)
    for i in range(0, len(global_list)):
        _dict = {}
        cnt = 0
        for j in range(0, len(global_list[i])):
            for k in range(0, len(final_list[global_list[i][j]])):
                if _dict.get(final_list[global_list[i][j]][k]) is None:
                    _dict[final_list[global_list[i][j]][k]] = 1
                    cnt += 1
            if cnt == max_number:
                #print("dhuki ",cnt, j, len(global_list[i]))
                if j != (len(global_list[i])-1):
                    return False
        #print(global_list[i], cnt, _dict)
        if cnt != max_number:
            return False
    return True


def solution(num_buns, num_required):
    # print(tree_dict)

    if num_required == 0:
        _list = []
        for i in range(0, num_buns):
            _list.append([])
        return _list#, True
    if num_required == 1 or num_required == 0:
        _list = []
        for i in range(0, num_buns):
            _list.append([0])
        return _list #, True
    if num_required == num_buns:
        _list = []
        for i in range(0, num_buns):
            _list.append([i])
        return _list #, True
    save = []
    for i in range(0, num_buns):
        save.append([])
    local_list = []
    base_group = []
    generation(k=num_required, st=0, en=num_buns - 1, local_list=local_list, global_list=base_group)
    for K in range(num_buns, -1, -1): # num_required+1
        local_list = []
        global_list = []
        generation(k=K, st=0, en=num_buns-1, local_list=local_list, global_list=global_list)
        final_ans = []
        # print(len(global_list))
        #print(global_list)
        for j in range(0, num_buns):
            final_ans.append([])
        for i in range(0, len(global_list)):
            for j in range(0, len(global_list[i])):
                final_ans[global_list[i][j]].append(i)
        verdict = verify(final_list=final_ans, global_list=base_group, max_number=len(global_list))
        # print(final_ans, verdict)
        if verdict is True:
            return final_ans
            # print(final_ans, verdict)
            save.clear()
            for i in range(0, len(final_ans)):
                save.append([])
                for j in range(0, len(final_ans[i])):
                    save[i].append(final_ans[i][j])
            # return final_ans # , verdict
    return save

"""
for j in range(1, 10):
    base = j
    for i in range(0, base+1):
        verdict = solution(base, i)
        if verdict is None:
            print("problem ",base, i)
            print("verdict ",verdict[0])
        else:
            print(base, i, "smooth", verdict)
            # break

"""
# print(solution(6, 2))
