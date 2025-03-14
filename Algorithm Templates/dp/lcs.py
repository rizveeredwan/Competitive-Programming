class LCS:
    def __init__(self):
        self.dp = {}
        self.path = {}

    def clear_memory(self):
        self.dp.clear()
        self.path.clear()

    def recursion(self, i, j, M, N):
        if i >= len(M) or j >= len(N):
            return 0
        if self.dp.get(i) is not None and self.dp.get(i).get(j) is not None:
            return self.dp[i][j]
        res1 = 0
        if M[i] == N[j]:
            res1 = max(res1, 1 + self.recursion(i + 1, j + 1, M, N))
            if self.path.get(i) is None:
                self.path[i] = {}
            if self.path.get(i).get(j) is None:
                self.path[i][j] = 0  # [i+1, j+1]
        else:
            res2 = self.recursion(i + 1, j, M, N)
            res3 = self.recursion(i, j + 1, M, N)
            if res2 >= res3:
                res1 = res2
                if self.path.get(i) is None:
                    self.path[i] = {}
                if self.path.get(i).get(j) is None:
                    self.path[i][j] = 1  # [i+1, j]
            else:
                res1 = res3
                if self.path.get(i) is None:
                    self.path[i] = {}
                if self.path.get(i).get(j) is None:
                    self.path[i][j] = 2  # [i, j+1]
        if self.dp.get(i) is None:
            self.dp[i] = {}
        if self.dp[i].get(j) is None:
            self.dp[i][j] = 0
        self.dp[i][j] = res1
        return self.dp[i][j]
    
    def get_path(self, i, j, M, N):
        if i >= len(M) or j >= len(N):
            return ""
        if self.path[i][j] == 0:
            _string = M[i] + self.get_path(i + 1, j + 1, M, N)
        elif self.path[i][j] == 1:
            _string = self.get_path(i + 1, j, M, N)
        elif self.path[i][j] == 2:
            _string = self.get_path(i, j + 1, M, N)
        return _string

    def key_exist(self, i, j):
        if self.dp.get(i) is not None and self.dp[i].get(j) is not None:
            return True
        return False

    def small_lcs(self, i, j, M, N, best, curr):
        if i >= len(M) or j >= len(N):
            print("dhuki ", curr)
            if len(best) == 0:
                for i in range(0, len(curr)):
                    best.append(curr[i])
            else:
                for i in range(0, len(best)):
                    if best[i] > curr[i]:
                        for j in range(0, len(curr)):
                            best[j] = curr[j]
                        break
            return
        assert(i < len(M) and j < len(N))
        if M[i] == N[j]:
            curr.append(M[i])
            self.small_lcs(i + 1, j + 1, M, N, best, curr)
            curr.pop()
        elif self.key_exist(i,j+1) is True and self.key_exist(i+1,j) is True and self.dp[i][j + 1] > self.dp[i + 1][j]:
            self.small_lcs(i, j + 1, M, N, best, curr)
        elif self.key_exist(i,j+1) is True and self.key_exist(i+1,j) is True and self.dp[i][j + 1] < self.dp[i + 1][j]:
            self.small_lcs(i + 1, j, M, N, best, curr)
        elif self.key_exist(i,j+1) is True and self.key_exist(i+1,j) is True and self.dp[i][j + 1] == self.dp[i + 1][j]:
            self.small_lcs(i, j + 1, M, N, best, curr)
            self.small_lcs(i + 1, j, M, N, best, curr)
        elif self.key_exist(i,j+1) is False and self.key_exist(i+1,j) is True:
            self.small_lcs(i + 1, j, M, N, best, curr)
        elif self.key_exist(i, j + 1) is True and self.key_exist(i + 1, j) is False:
            self.small_lcs(i, j+1, M, N, best, curr)
        return

    def begin_matching(self, M, N):
        self.clear_memory()
        res = self.recursion(0, 0, M, N)
        print(res)
        return res

    def return_path(self, M, N):
        _string = self.get_path(0, 0, M, N)
        print(_string)

    def return_copy_of_dp(self):
        arr = {}
        for key1 in self.dp:
            arr[key1] = {}
            for key2 in self.dp[key1]:
                arr[key1][key2] = self.dp[key1][key2]
        return arr

    def print_table(self, M, N):
        for i in range(0, len(M)):
            _string = ""
            for j in range(0, len(N)):
                val = "NONE"
                if (self.dp.get(i) is not None and self.dp.get(i).get(j) is not None):
                    val = str(self.dp[i][j])
                _string = _string + " " + val 

            print(_string)
        return 
    
    def itr_lcs_matching(self, M, N):
        dp = {}
        dp[0] = {}
        dp[0][0] = 0
        for i in range(0, len(N)):
            dp[0][i+1] = 0 
        for i in range(0, len(M)):
            if dp.get(i+1) is None:
                dp[i+1]={}
            dp[i+1][0] = 0 
        for i in range(0, len(M)):
            for j in range(0, len(N)):
                if M[i] == N[j]:
                    dp[i+1][j+1] = 1+dp[i][j]
                else:
                    dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]) 
        print("PRINT")
        for i in range(0, len(M)+1):
            temp = ""
            for j in range(0, len(N)+1):
                temp = temp + str(dp[i][j])
            print(temp)
        


if __name__ == '__main__':
    lcs = LCS()
    M="DABBCCCBA"
    N="CABCABCACB"
    lcs.begin_matching(M=M, N=N)
    lcs.itr_lcs_matching(M=M, N=N)
    #lcs.return_path(M=M, N=N)
    #lcs.print_table(M=M, N=N)
    #best = []
    #lcs.small_lcs(i=0, j=0, M=M, N=N, best=best, curr=[])
    #print("".join(i for i in best))
