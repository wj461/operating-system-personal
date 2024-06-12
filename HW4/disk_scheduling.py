import random

random_list = [random.randint(0, 4999) for i in range(1000)]
print(random_list)

start = input("Input initial position of the disk head : ")

def cal_two_points_distance(point1, point2):
    return abs(point1 - point2)

def FCFS(start, random_list):
    total_distance = 0
    current = start
    for i in random_list:
        total_distance += cal_two_points_distance(current, i)
        current = i
    return total_distance

def SCAN(start, random_list):
    if 0 not in random_list:
        random_list.append(0)

    total_distance = 0
    current = start
    random_list = sorted(random_list)
    for i in random_list:
        total_distance += cal_two_points_distance(current, i)
        current = i

    if len(random_list) == 1001:
        random_list.remove(0)
    return total_distance


def closest(lst, K):
    return lst[min(range(len(lst)), key = lambda i: abs(lst[i]-K))]

def CSCAN(start, random_list):
    total_distance = 0
    random_list = sorted(random_list)
    close_num = closest(random_list, start)
    front = random_list[:random_list.index(close_num)]
    back = random_list[random_list.index(close_num):]

    current = 0
    for i in front:
        total_distance += cal_two_points_distance(current, i)
        current = i

    current = start
    for i in back:
        total_distance += cal_two_points_distance(current, i)
        current = i
    
    return total_distance

print("FCFS: ", FCFS(int(start), random_list))
print("SCAN: ", SCAN(int(start), random_list))
print("CSCAN: ", CSCAN(int(start), random_list))