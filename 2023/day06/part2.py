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

tot_time = ''
for time in times:
    tot_time += time

tot_dist = ''
for dist in distances:
    tot_dist += dist
   
time = float(tot_time)
distance = float(tot_dist)

t1 = time/2 + sqrt((time/2)*(time/2) - distance)
t2 = time/2 - sqrt((time/2)*(time/2) - distance)
t1 = min(ceil(t1-1), time)
t2 = max(floor(t2+1), 1)

total = t1 - t2 + 1
print(total)