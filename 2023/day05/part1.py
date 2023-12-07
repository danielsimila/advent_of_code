from pathlib import Path

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

lines = Path('day05/example.txt') 
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

locations = []
for seed in seeds:
    number = int(seed)
    for i in range(len(idxs)-1):
        number = get_mapped_number(number, lines[lines.index(idxs[i]):lines.index(idxs[i+1])])

    locations.append(number)

print(min(locations))