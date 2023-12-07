from pathlib import Path
from numpy import sqrt

def get_mapped_number(test_no, range):
    mapped_no = test_no
    for index, line in enumerate(range):
        if index == 0 or (line == ''):
            continue

        numbers = line.split(' ')
        destination_range_start = int(numbers[0])
        source_range_start = int(numbers[1])
        range = int(numbers[2])

        if test_no >= source_range_start and test_no < (source_range_start+range):
            mapped_no = destination_range_start + (test_no - source_range_start)
            break

    return mapped_no

lines = Path('day05/input.txt') 
lines = lines.read_text().split('\n')

trash, seeds = lines[0].split(':')
seeds = seeds.strip().split(' ')

lines = lines[2:-1]
lines.append('end')

idxs = ['seed-to-soil map:',
    'soil-to-fertilizer map:',
    'fertilizer-to-water map:',
    'water-to-light map:',
    'light-to-temperature map:',
    'temperature-to-humidity map:',
    'humidity-to-location map:',
    'end']

# make this into function... return mapped value and recurse
test_no = 79
mapped_no = -1
mapped_no = get_mapped_number(test_no, lines[lines.index(idxs[0]):lines.index(idxs[1])] )

min_location = 0
min_seed = 0
for index, seed in enumerate(seeds):
    if index % 2 == 0: 
        continue
    
    start_no = int(seeds[index-1])
    range_no = int(seeds[index])
    loop_no = int(start_no)
    while loop_no < start_no + range_no:
        number = int(loop_no)
        for i in range(len(idxs)-1):
            number = get_mapped_number(number, lines[lines.index(idxs[i]):lines.index(idxs[i+1])])

        if number < min_location or min_location == 0:
            min_location = number
            min_seed = loop_no
        
        loop_no += int(sqrt(range_no))

print("Frist loop done!")

for index, seed in enumerate(seeds):
    if index % 2 == 0: 
        continue
    
    start_no = int(seeds[index-1])
    range_no = int(seeds[index])
    loop_no = int(start_no)
    if start_no <= min_seed <= start_no+range_no:
        start_no = min_seed - sqrt(range_no)
        range_no = sqrt(range_no)
        loop_no =start_no
        while loop_no < start_no + range_no: 
            number = int(loop_no)
            for i in range(len(idxs)-1):
                number = get_mapped_number(number, lines[lines.index(idxs[i]):lines.index(idxs[i+1])])

            if number < min_location or min_location == 0:
                min_location = number
                min_seed = loop_no
            
            loop_no += 1

print('Second loop done!\nMin location: ', min_location)