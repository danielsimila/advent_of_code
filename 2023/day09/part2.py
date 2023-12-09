from pathlib import Path

lines = Path('day09/input.txt').read_text().split('\n')

def find_first_number(numbers):
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
        return numbers[0]
    else: 
        return numbers[0] - find_first_number(diffs)
    
sum = 0
for line in lines:
    line = line.split(' ')
    for index, nr in enumerate(line):
        line[index] = int(nr)

    sum += find_first_number(line)

print('Sum: ', sum)
