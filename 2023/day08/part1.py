from pathlib import Path

lines = Path('day08/input.txt').read_text().split('\n')

instruction = lines[0]

lines = lines[2:-1]

mapping = {}
for line in lines:
    key, mappings = line.split(' = ')
    m1, m2 = mappings.split(', ')
    mapping[key] = (m1[1:], m2[0:3])

pos = 'AAA'
step = 0
while pos != 'ZZZ':
    direction = instruction[step % len(instruction)]
    direction = (direction == 'R')
    pos = mapping[pos][direction] 
    step += 1

print('Total steps: ', step)