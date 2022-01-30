from math import floor

def binary_search(array, sr):
    st, en = 0, len(array)-1
    cnt  = 0
    while st<en:
        print(st, en)
        cnt  = cnt + 1
        if (en-st) <= 1:
            if en<sr:
                return cnt
            if st<sr:
                return cnt
        mid = floor((st+en)/2)
        if sr < array[mid]:
            en = mid-1
        else:
            st = mid
    return cnt


array = [ 1, 5, 7, 10, 17, 29, 35, 47, 49, 51, 53, 107, 125, 137]
sr=108
print(binary_search(array, sr))
