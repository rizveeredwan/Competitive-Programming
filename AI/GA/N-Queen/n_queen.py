import random


class GeneticAlgo:
    def __init__(self):
        pass

    def initial_population(self, pop_sz=6, n=8):
        population = []
        for i in range(0, pop_sz):
            population.append([[], None])
            while len(population[-1][0]) < n:
                value = random.randint(0, n * n - 1)
                if value not in population[-1][0]:
                    population[-1][0].append(value)
            population[-1][1] = self.single_instance_problem(sample=population[-1][0])
        return population

    def selection(self):
        # will be selecting the weakest/problematic most twos
        pass

    def crossover(self, sample1, sample2):
        #print(sample1)
        #print(sample2)
        _list = []
        for i in range(0, len(sample1)):
            _list.append(sample1[i])
            _list.append(sample2[i])
        _list1 = _list[0:int(len(_list)/2)]
        _list2 = _list[int(len(_list)/2):len(_list)]
        assert(len(_list1) == len(_list2))
        return _list1, _list2

    def mutation(self, _list):
        # print("starting ", _list)
        flag = False
        _dict = {}
        for i in range(0, len(_list)):
            if _dict.get(_list[i]) is None:
                _dict[_list[i]] = 0
            _dict[_list[i]] += 1
            if _dict[_list[i]] > 1:
                flag = True
        if flag is True:
            for i in range(0, len(_list)):
                if _dict[_list[i]] > 1:
                    _dict[_list[i]] -= 1
                    while True:
                        v = random.randint(0, (len(_list) * len(_list)) - 1)
                        if _dict.get(v) is None:
                            _dict[v] = 1
                            _list[i] = v
                            break
        if flag is False:
            idx = random.randint(0, len(_list)-1)
            while True:
                v = random.randint(0, (len(_list) * len(_list))-1)
                if v not in _list:
                    _list[idx] = v
                    break
        return _list

    def single_instance_problem(self, sample):
        attack = 0
        for i in range(0, len(sample)):
            for j in range(i + 1, len(sample)):
                if abs(sample[j] - sample[i]) <= 7: # row problem
                    attack += 1
                elif abs(sample[j] - sample[i])%8 == 0:
                    attack += 1 # column problem
                elif abs(sample[j] - sample[i])%7 == 0:
                    attack += 1 # right diagonal
                elif abs(sample[j] - sample[i])%9 == 0:
                    attack += 1 # left diagonal
        return attack

    def fitness(self, population):
        # calculate the fitness
        total = 0
        for i in range(0, len(population)):
            total += population[-i][1]
        return total

    def check_problems(self, child1):
        for i in range(0, len(child1)):
            for j in range(i+1, len(child1)):
                assert(child1[i] != child1[j])

    def single_block_of_execution(self, population, version):
        if version == 1:
            # random shuffling
            random.shuffle(population)
        # selection & crossover
        child1, child2 = self.crossover(sample1=population[-1][0], sample2=population[-2][0])
        # print(child1, child2)
        # mutation
        child1 = self.mutation(_list=child1)
        child2 = self.mutation(_list=child2)
        #self.check_problems(child1=child1)
        #self.check_problems(child1=child2)
        a1 = self.single_instance_problem(sample=child1)
        a2 = self.single_instance_problem(sample=child2)
        population.append([child1, a1])
        population.append([child2, a2])
        # deleation
        population.sort(key=lambda x: x[1], reverse=False)
        del population[-1]
        del population[-1]

    def print_population(self, population, f):
        if f == 0:
            for i in range(0, len(population)):
                _str = str(population[i][0][0])
                for j in range(1, len(population[i][0])):
                    _str = _str + " " + str(population[i][0][j])
                print(f"sample No. {i} = {_str}")
                print(f"fitness = {population[i][1]}")
        else:
            _str = str(population[0][0][0])
            for j in range(1, len(population[0][0])):
                _str = _str + " " + str(population[0][0][j])
            print(f"Current Best {_str}")
            print(f"fitness = {population[0][1]}")

    def algorithm(self, iteration, population_size=6, n=8):
        population = self.initial_population(pop_sz=population_size, n=n)
        population.sort(key=lambda x: x[1], reverse=False)
        self.print_population(population=population, f=0)
        for i in range(1, iteration):
            # selection & crossover
            temp = str(population)
            # generic one
            self.single_block_of_execution(population, version=0)
            if str(population) == temp:
                # failed, random one
                self.single_block_of_execution(population, version=1)
            # print(f"size = {len(population)} iteration = {i}, population = {population}, fitness = {self.fitness(population=population)}")
            if i%10000 == 0:
                print(f"iteration {i}")
                self.print_population(population=population, f=1)

obj = GeneticAlgo()
obj.algorithm(iteration=100000, population_size=6, n=8)
