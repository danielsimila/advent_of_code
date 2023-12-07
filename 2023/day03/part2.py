from pathlib import Path
from numpy import zeros, ones
import re

txt = Path('day03/input.txt').read_text()
lines = txt.split('\n')

sum = 0
gearmap = zeros((len(lines),len(lines[0])), dtype=int)
gearvalues = ones((len(lines),len(lines[0])), dtype=int)

for index, line in enumerate(lines):
    tmp = re.split('[^\d]', line) 
    numbers = []
    for number in tmp:
        if number != '':
            numbers.append(number)
    
    if numbers != []:
        for number in numbers:
            start_idx = max(0, line.find(number) - 1)
            end_idx = min(len(line), line.find(number) + 1 + len(number))
            line_up_idx = index - 1
            line_down_idx = index + 1
            
            for line_idx in [line_up_idx, index, line_down_idx]:
                if line_idx >= len(lines) or line_idx < 0:
                    continue
                
                str = lines[line_idx][start_idx:end_idx]
                for ch_idx, ch in enumerate(str): 
                    if ch == '*':
                        gearmap[line_idx][start_idx+ch_idx] += 1
                        gearvalues[line_idx][start_idx+ch_idx] *= int(number)

            # Remove number from line...
            dots = ''
            for ch in number:
                dots += '.'
            line = line.replace(number, dots, 1)

for line_idx, line in enumerate(gearmap):
    for id_idx, id in enumerate(line):
        if id == 2:
            sum += gearvalues[line_idx][id_idx]

print(sum)
