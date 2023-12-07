from pathlib import Path
from numpy import sqrt
from math import ceil, floor

def remove_empty(list):
    new_list = []
    for item in list:
        if item == '' or item == []:
            continue
        new_list.append(item)

    return new_list

txt = Path('day06/input.txt').read_text()
lines = txt.split('\n')

trash, times = lines[0].split(':')
trash, distances = lines[1].split(':')

times = times.strip().split(' ')
distances = distances.strip().split(' ')
times = remove_empty(times)
distances = remove_empty(distances)

sum = 1
for index in range(len(times)): 
    time = float(times[index])
    distance = float(distances[index])
 
    t1 = time/2 + sqrt((time/2)*(time/2) - distance)
    t2 = time/2 - sqrt((time/2)*(time/2) - distance)
    t1 = min(ceil(t1-1), time)
    t2 = max(floor(t2+1), 1)

    total = t1 - t2 + 1
    sum *= total

print(sum)