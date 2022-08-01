import random

class EightPuzzle:
    def __init__(self):
        pass

    def h_function2(self, current_state, goal_state):
        cnt = 0
        for i in range(0, len(current_state)):
            for j in range(0, len(current_state[i])):
                if current_state[i][j] != goal_state[i][j]:
                    cnt = cnt+1
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
                        x = i+dx[k]
                        y = j+dy[k]
                        if 0 <= x <= 2 and 0 <= y <= 2:
                            ns = self.copy(current_state=current_state)
                            ns[i][j] = ns[x][y]
                            ns[x][y] = 'X'
                            next_states.append(ns)
                    break
        return next_states

    def hill_climbing(self, initial_state, goal_state, stochastic=False):
        h = self.h_function(current_state=initial_state, goal_state=goal_state)
        current_state = initial_state
        best_h_val = h
        while True:
            print(current_state, best_h_val)
            next_states = self.generate_next_moves(current_state=current_state)
            random.shuffle(next_states)
            if len(next_states) == 0:
                break
            best_ns = None
            for i in range(0, len(next_states)):
                h_new = self.h_function(current_state=next_states[i], goal_state=goal_state)
                print("i = ", next_states[i], h_new)
                if best_h_val > h_new: # better state/close to goal
                    best_h_val = h_new
                    best_ns = i
                    if stochastic is True:
                        break
            if best_ns is not None: # found a solution
                current_state = next_states[best_ns]
                h = best_h_val
            else:
                break
        print(current_state)


def problem_input():
    start_state = [['X', 7, 2], [1, 6, 3], [4, 5, 8]]
    goal_state = [['X', 1, 2], [3, 4, 5], [6, 7, 8]]
    return start_state, goal_state


if __name__ == '__main__':
    obj = EightPuzzle()
    start_state, goal_state = problem_input()
    obj.hill_climbing(initial_state=start_state, goal_state=goal_state, stochastic=False)
    #print(obj.h_function(start_state, goal_state))
    next_states = obj.generate_next_moves(current_state=start_state)
    for n in next_states:
        print(obj.h_function(n, goal_state))
    #print(obj.generate_next_moves(current_state=start_state))
    
