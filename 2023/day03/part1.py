from pathlib import Path
import re

txt = Path('day03/input.txt').read_text()
lines = txt.split('\n')

sum = 0

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
            line_up_idx = max(0, index - 1)
            line_down_idx = min(len(lines)-1, index + 1)
            
            valid = 0
            for line_idx in [line_up_idx, index, line_down_idx]:
                str = lines[line_idx][start_idx:end_idx]
                for ch in str: 
                    if not ch.isnumeric() and ch != '.':
                        valid = 1
            
            if valid == 1:
                sum += int(number)
            
            dots = ''
            for ch in number:
                dots += '.'
            line = line.replace(number, dots, 1)
            
print(sum)
