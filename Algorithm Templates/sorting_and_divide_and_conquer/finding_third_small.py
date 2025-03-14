from math import floor

def merge(Left, Right):
    i, j = 0, 0 
    final_merged = [None, None, None]
    for k in range(0, 3):
        if Left[i] != None and Right[j] != None:
            if Left[i] <= Right[j]:
                final_merged[k] = Left[i] 
                i += 1  
            else:
                final_merged[k] = Right[j]
                j += 1
        elif Left[i] != None:
            final_merged[k] = Left[i] 
            i += 1 
        elif Right[j] != None:
            final_merged[k] = Right[j]
            j += 1
        else: # no value can not be taken 
            break 
    return final_merged

def merge_sort(A, st, en):
    if st == en:
        return [A[st], None, None]
    if (en-st) == 1:
        if A[st] > A[en]:
           return [A[en], A[st], None]
        else: 
            return [A[st], A[en], None]
    mid = floor((st+en)/2)
    Left = merge_sort(A, st, mid)
    Right = merge_sort(A, mid+1,en)
    final_merged = merge(Left, Right)
    return final_merged

final_res = merge_sort([10, 12, 3, 6, 17, 2, 9, 11, 20, 25, 71, 4], st=0, en=11)
print(final_res)


def shift(_list, st):
    en = 1
    for i in range(en, st-1, -1):
        _list[i+1] = _list[i]
    return _list  

def find_pos(_list, value):
    if _list[0] is None:
        _list[0] = value 
        return 
    elif value < _list[0]:
        _list = shift(_list, 0)
        _list[0] = value 
    elif _list[1] is None:
        _list[1] = value 
        return 
    elif value < _list[1]:
        _list = shift(_list, 1) 
        _list[1] = value 
    elif _list[2] is None:
        _list[2] = value 
        return 
    elif value < _list[2]:
        _list[2] = value 
    

def process(A):
    _list =[None, None, None]
    for i in range(0, len(A)):
        find_pos(_list, A[i])
        print(_list, i, A[i])
    print(_list)

process([10, 12, 3, 6, 17, 2, 9, 11, 20, 25, 71, 4])
