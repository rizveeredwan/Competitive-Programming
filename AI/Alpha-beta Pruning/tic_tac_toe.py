import random


class TicTacToe:
    def __init__(self):
        pass

    def copy_with_new_move(self, board, r, c, value):
        new_board = []
        for i in range(0, len(board)):
            new_board.append([])
            for j in range(0, len(board[i])):
                new_board[i].append(board[i][j])
        new_board[r][c] = value
        return new_board

    def generate_next_moves(self, board, value):
        save = []
        for i in range(0, len(board)):
            for j in range(0, len(board[i])):
                if board[i][j] == '':
                    n = self.copy_with_new_move(board=board, r=i, c=j, value=value)
                    save.append(n)
        return save

    def cal_score(self, board):
        flow = 1
        for i in range(0, len(board)):
            if i == 0 or board[i][i] == board[i - 1][i - 1]:
                flow = 1
            else:
                flow = 0
                break
        if flow == 1:
            if board[0][0] == 'x':
                return 1
            elif board[0][0] == 'o':
                return -1
        flow = 1
        for i in range(0, len(board)):
            if i == 0 or board[i][len(board) - i - 1] == board[i - 1][len(board) - i]:
                flow = 1
            else:
                flow = 0
                break
        if flow == 1:
            if board[0][len(board) - 1] == 'x':
                return 1
            elif board[0][len(board) - 1] == 'o':
                return -1
        # row match
        for i in range(0, len(board)):
            flow = 1
            for j in range(1, len(board[i])):
                if board[i][j] == board[i][j - 1]:
                    flow = 1
                    continue
                else:
                    flow = 0
                    break
            if flow == 1:
                if board[i][0] == 'x':
                    return 1
                elif board[i][0] == 'o':
                    return -1
            flow = 1
            for j in range(1, len(board[i])):
                if board[j][i] == board[j - 1][i]:
                    flow = 1
                    continue
                else:
                    flow = 0
                    break
            if flow == 1:
                if board[0][i] == 'x':
                    return 1
                elif board[0][i] == 'o':
                    return -1
        return None

    def minimax_with_alpha_beta_pruning(self, board, alpha, beta, player_level):
        score = self.cal_score(board=board)
        #print("score ", score, board)
        if score is not None:
            return score, board  # someone is winner
        if player_level == 'max':
            value = 'x'
            v = -5  # infinity
            best_mv = None
        else:
            value = 'o'
            v = 5  # infinity
            best_mv = None
        next_moves = self.generate_next_moves(board, value)
        if len(next_moves) == 0:
            return 0, None  # draw
        for i in range(0, len(next_moves)):
            if player_level == 'min':
                mv, _ = self.minimax_with_alpha_beta_pruning(board=next_moves[i], alpha=alpha, beta=beta,
                                                             player_level='max')
                if mv < v:
                    v = mv
                    best_mv = next_moves[i]
                if v <= alpha:
                    return v, next_moves[i]
                beta = min(beta, v)
            elif player_level == 'max':
                mv, _ = self.minimax_with_alpha_beta_pruning(board=next_moves[i], alpha=alpha, beta=beta,
                                                             player_level='min')
                if mv > v:
                    v = mv
                    best_mv = next_moves[i]
                if v >= beta:
                    return v, next_moves[i]
                alpha = max(alpha, v)
        return v, best_mv


def printf(board):
    for i in range(0, len(board)):
        if board[i][0] == '':
            _string = '_'
        else:
            _string = board[i][0]
        for j in range(1, len(board[i])):
            if board[i][j] == '':
                _string = _string + " " + "_"
            else:
                _string = _string + " " + board[i][j]
        print(_string)


if __name__ == '__main__':
    def base():
        obj = TicTacToe()
        board = [['x', '', 'x'], ['', 'o', ''], ['o', '', '']]
        input_player = 'min'  # or max
        res, mv = obj.minimax_with_alpha_beta_pruning(board=board, alpha=-5, beta=5, player_level=input_player)
        if res == 1:
            print("winner is max")
            if input_player == 'max':
                assert (mv is not None)
                printf(mv)
        elif res == -1:
            print("winner is min")
            if input_player == 'min':
                assert (mv is not None)
                printf(mv)
        else:
            print("draw")


    #base()


    def board_input():
        board = [['', '', ''], ['', '', ''], ['', '', '']]
        for i in range(0, 3):
            line = input()
            for j in range(0, 3):
                board[i][j] = line[j]
                if board[i][j] == '_':
                    board[i][j] = ''
        return board

    def board_simple(board):
        while True:
            x, y = int(input()), int(input())
            if board[x][y] == '':
                board[x][y] = 'x'
                return board
            else:
                print("incorrect move")

    def interactive():
        inp = random.randint(0, 1)
        obj = TicTacToe()
        if inp == 0:
            print("Computer will give first move")
            board = [['', '', ''], ['', '', ''], ['', '', '']]
            input_player = 'min'  # or max
            res, mv = obj.minimax_with_alpha_beta_pruning(board=board, alpha=-5, beta=5, player_level=input_player)
            alter = 'max'
            board = mv
        else:
            print("You will give first move")
            board = board_input()
            alter = 'min'
        res = None
        for i in range(2, 10, 2):
            if alter == 'max':
                print("current board", board)
                printf(board)
                print("your move = ")
                board = board_simple(board)
                input_player = 'min'  # or max
                res, mv = obj.minimax_with_alpha_beta_pruning(board=board, alpha=-5, beta=5, player_level=input_player)
                board = mv
            if alter == 'min':
                input_player = 'min'  # or max
                res, mv = obj.minimax_with_alpha_beta_pruning(board=board, alpha=-5, beta=5, player_level=input_player)
                board = mv
                print("current board", board)
                printf(board)
                print("your move = ")
                board = board_simple(board)
                if res == 0:
                    print("game will be drawn")
                    #return
            if res == -1:
                print("Computer Won")
                return
            if res == 1:
                print("You Won")
                return
    interactive()