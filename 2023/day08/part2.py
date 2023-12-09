from pathlib import Path
import math

lines = Path('day08/input.txt').read_text().split('\n')

instruction = lines[0]

lines = lines[2:-1]

mapping = {}
positions = []
goal_positions = []
for line in lines:
    key, mappings = line.split(' = ')
    m1, m2 = mappings.split(', ')
    mapping[key] = (m1[1:], m2[0:3])
    
    if key[-1] == 'A':
        positions.append(key)
        goal_positions.append(0)

step = 1
in_goal = 0
while not in_goal:
    in_goal = 1
    direction = instruction[(step-1) % len(instruction)]
    if direction == 'R':
        direction = 1
    else:
        direction = 0

    for index, pos in enumerate(positions):
        pos = mapping[pos][direction]
        positions[index] = pos
        if pos[-1] != 'Z':
            in_goal = 0
        else: 
            if goal_positions[index] == 0:
                goal_positions[index] = step

    if (step > 100000):
            in_goal = 1  

    step += 1

print(goal_positions)
print('LCM (hardcode values as input): ', math.lcm(21883, 13019, 19667, 16343, 18559, 14681))