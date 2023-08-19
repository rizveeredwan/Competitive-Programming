value = 43
num_of_itr = 0
while value > 0:
    temp = value ^ (value-1)
    temp = value & temp
    value = value ^ temp
    num_of_itr += 1
print("number of iterartions ", num_of_itr)
