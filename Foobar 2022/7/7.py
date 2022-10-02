
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

PRINT_FLAG = False


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


def solution_generation(global_list, max_number, max_size, bunny_no, idx_no, max_bunny_no, tree_dict, num_required,
                        ref_list, freq_array):
    # print(global_list)
    if bunny_no >= max_bunny_no: # all done
        return True
    if idx_no == max_size:
        # a possible solution generated for a single bunny
        verdict = verify_union_v2(id=bunny_no, global_list=global_list, ref_list=ref_list, max_number=max_number,
                                  max_depth=num_required)

        # print("verdict of union ", verdict, bunny_no, max_number, global_list)
        if verdict is True:
            return solution_generation(global_list=global_list, max_number=max_number,
                                       max_size=max_size, bunny_no=bunny_no+1, idx_no=0, max_bunny_no=max_bunny_no,
                                       tree_dict=tree_dict, num_required=num_required, ref_list=ref_list, freq_array=freq_array)
        else:
            return False
    # currently working with bunny_no
    st = 0
    if bunny_no > 0:
        st = global_list[bunny_no-1][idx_no]
        if idx_no > 0:
            st = max(st,  global_list[bunny_no][idx_no-1]+1)
    else:
        if idx_no > 0:
            st = global_list[bunny_no][idx_no-1]+1
    for j in range(st, max_number+1):
        """
        if freq_array[j] == num_required:
            continue
        """
        freq_array[j] += 1 # bound on frequency
        # print("idx , bunny ", bunny_no, idx_no, global_list[bunny_no])
        global_list[bunny_no][idx_no] = j  # solution done
        verdict = solution_generation(global_list=global_list, max_number=max_number,
                                      max_size=max_size, bunny_no=bunny_no, idx_no=idx_no+1,
                                      max_bunny_no=max_bunny_no,
                                      tree_dict=tree_dict, num_required=num_required, ref_list=ref_list,
                                      freq_array=freq_array) # getting solution
        if verdict is False:
            global_list[bunny_no][idx_no] = None  # trying with next one
            freq_array[j] -= 1 # bound on frequency
        else:
            return True  # done
    return False  # solution is not complete


def print_tree(tree_dict):
    for key in tree_dict:
        print(key, tree_dict)


def print_ref_list(ref_list):
    for key in ref_list:
        print(key, len(ref_list[key]))


def solution(num_buns, num_required):
    local_list = []
    global_list = []
    generation(k=num_required, st=0, en=num_buns, local_list=local_list, global_list=global_list)
    # print("global list = ", global_list)
    tree_dict, ref_list = generate_tree(global_list)
    # print(tree_dict)
    if num_required == 0:
        _list = []
        for i in range(0, num_buns):
            _list.append([])
        return _list
    if num_required == 1:
        _list = []
        for i in range(0, num_buns):
            _list.append([0])
        return _list
    if num_required == num_buns:
        _list = []
        for i in range(0, num_buns):
            _list.append([i])
        return _list
    max_number = 0
    max_size = 1
    while True:
        # print(global_list)
        # print(max_number, max_size)
        # print_tree(tree_dict)
        """
        if ((max_number+1) * num_required) % num_buns == 0:
            max_size = int((max_number+1) * num_required / num_buns)
        else:
            max_number += 1
            continue
        """
        global_list = []
        freq_array = {}
        for i in range(0, max_number+1):
            freq_array[i] = 0
        for i in range(0, num_buns):
            global_list.append([])
            for j in range(0, max_size):
                global_list[i].append(None)
                if i == 0:
                    global_list[i][j] = j
                    freq_array[j] += 1

        verify_union_v2(id=0, global_list=global_list, ref_list=ref_list, max_number=max_number, max_depth=num_required)
        print(max_number, max_size)
        #print(global_list)
        #print(freq_array)
        verdict = solution_generation(global_list=global_list, max_number=max_number, max_size=max_size,
                                      bunny_no=1, idx_no=0, max_bunny_no=num_buns, tree_dict=tree_dict,
                                      num_required=num_required, ref_list=ref_list, freq_array=freq_array)
        # print("verdict completed = ", verdict)
        if verdict is True:
            break
        else:
            # max_number += 1
            # print(freq_array)

            max_size += 1
            if max_size > (max_number+1):
                max_size = 1
                max_number += 1

    return global_list


print(solution(6, 2))
