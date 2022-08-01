import sys
import heapq


class AStarNode:
    def __init__(self, state, g_value, h_value):
        self.state = state
        self.g = g_value
        self.h = h_value

    def __lt__(self, other):
        if (self.g + self.h) < (other.g + other.h):
            return True
        return False


class AStar:
    def __init__(self):
        self.dict = {}

    def h_function2(self, current_state, goal_state):
        cnt = 0
        for i in range(0, len(current_state)):
            for j in range(0, len(current_state[i])):
                if current_state[i][j] != goal_state[i][j]:
                    cnt = cnt + 1
        return cnt

    def h_function(self, current_state, goal_state):
        h = 0
        for i in range(0, len(current_state)):
            for j in range(0, len(current_state[i])):
                for k in range(0, len(goal_state)):
                    for l in range(0, len(goal_state[k])):
                        if current_state[i][j] == goal_state[k][l] and current_state[i][j] != 'X':
                            h = h + abs(i - k) + abs(j - l)
        return h

    def copy(self, current_state):
        next_state = []
        for i in range(0, len(current_state)):
            next_state.append([])
            for j in range(0, len(current_state[i])):
                next_state[i].append(current_state[i][j])
        return next_state

    def generate_next_moves(self, current_state):
        calc = False
        dx = [-1, 1, 0, 0]
        dy = [-0, 0, 1, -1]
        next_states = []
        for i in range(0, len(current_state)):
            if calc is True:
                break
            for j in range(0, len(current_state[i])):
                if current_state[i][j] == 'X':
                    calc = True
                    for k in range(0, len(dx)):
                        x = i + dx[k]
                        y = j + dy[k]
                        if 0 <= x <= 2 and 0 <= y <= 2:
                            ns = self.copy(current_state=current_state)
                            ns[i][j] = ns[x][y]
                            ns[x][y] = 'X'
                            next_states.append(ns)
                    break
        return next_states

    def a_star_algorithm(self, initial_state, goal_state):
        _list = []
        temp = AStarNode(state=initial_state, g_value=0, h_value=self.h_function(initial_state, goal_state))
        heapq.heappush(_list, temp)
        self.dict[str(initial_state)] = [None,0, temp.h]

        while len(_list) > 0:
            u = heapq.heappop(_list)
            #print(u.state)
            #print(u.g, u.h)
            if u.state == goal_state:
                #print("FOUND ", u.state)
                break
            next_states = self.generate_next_moves(current_state=u.state)
            #print(next_states)
            for i in range(0, len(next_states)):
                temp = AStarNode(state=next_states[i], g_value=u.g+1, h_value=self.h_function(next_states[i], goal_state))
                if self.dict.get(str(next_states[i])) is None:
                    self.dict[str(next_states[i])] = [u.state, u.g+1, temp.h]
                    heapq.heappush(_list, temp)
                elif self.dict.get(str(next_states[i]))[1] > (u.g+1):
                    self.dict[str(next_states[i])] = [u.state, u.g + 1, temp.h]
                    heapq.heappush(_list, temp)
        return

    def list_to_string(self, list):
        #print(list)
        _string = " ".join(str(i) for i in list).strip()
        return _string

    def path_print(self, initial_state, goal_state):
        _list = []
        curr = goal_state
        while curr is not None:
            _list.append(curr)
            assert(self.dict[str(curr)][0] != curr)
            # print(self.dict[str(curr)][0], self.dict[str(curr)][1])
            #print(curr, self.dict[str(curr)][1], self.dict[str(curr)][2])
            curr = self.dict[str(curr)][0]
            #print(curr)
            #input()
        _list.reverse()
        for i in range(0, len(_list)):
            print("step #{}".format(i+1))
            for j in range(0, len(_list[i])):
                print(self.list_to_string(_list[i][j]))


def problem_input():
    start_state = [['X', 7, 2], [1, 6, 3], [4, 5, 8]]
    goal_state = [['X', 1, 2], [3, 4, 5], [6, 7, 8]]
    return start_state, goal_state


if __name__ == '__main__':
    sys.stdout = open('out.txt', 'w')
    obj = AStar()
    start_state, goal_state = problem_input()
    #print(start_state, goal_state)
    obj.a_star_algorithm(initial_state=start_state, goal_state=goal_state)
    obj.path_print(initial_state=start_state, goal_state=goal_state)