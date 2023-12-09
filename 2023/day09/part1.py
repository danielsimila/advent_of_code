from pathlib import Path

lines = Path('day09/input.txt').read_text().split('\n')

def find_next_number(numbers):
    diffs = []
    all_zeros = 1
    for index in range(len(numbers)):
        if index == 0:
            continue

        diff = numbers[index] - numbers[index-1]
        diffs.append(diff)

        if diff != 0:
            all_zeros = 0
    
    if all_zeros:
        return numbers[-1]
    else: 
        return find_next_number(diffs) + numbers[-1]
    
sum = 0
for line in lines:
    line = line.split(' ')
    for index, nr in enumerate(line):
        line[index] = int(nr)
    
    sum += find_next_number(line)

print(sum)
