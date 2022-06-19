class CompareStateStyle1:
    def __init__(self, v):
        self.v = v  # // elements of the state

    def __lt__(self, a):
        # overloading operator <
        # with the base element (self): we are going to compare variable a
        if self.v < a.v:
            return True
        return False


class TicTacToeState:
    def __init__(self):
        self.arr = ['X', 'X', 'X', 'X', 'X', 'X' , 'X', 'X', 'X']

    def __eq__(self, a):
        # with the base element (self): we are going to compare variable a
        for i in range(0, len(self.arr)):
            if a.arr[i] > self.arr[i] or a.arr[i] < self.arr[i]:
                return False #  means that they are not same
        return True # means they are same


if __name__ == '__main__':
    c1 = CompareStateStyle1(10)
    c2 = CompareStateStyle1(20)
    print(c1 < c2, c2 < c1)

    t1 = TicTacToeState()
    t2 = TicTacToeState()
    print(t1 == t2)

    t2.arr[0] = '0'
    print(t1 == t2)
