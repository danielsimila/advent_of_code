from pathlib import Path
from random import randint
import time

def quicksort(array):
    if len(array) < 2:
        return array

    low, same, high = [], [], []
    pivot = array[randint(0, len(array) - 1)]

    for item in array:
        if right_hand_larger(item, pivot):
            low.append(item)
        else:
            high.append(item)

    return quicksort(low) + same + quicksort(high)


def right_hand_larger(lhand, rhand):
    types = ['A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2','J']

    if rhand[-1] == lhand[-1]:
        for i in range(5):
            if types.index(rhand[i]) == types.index(lhand[i]):
                continue
            else: 
                return  types.index(rhand[i]) < types.index(lhand[i])
    else:
        return rhand[-1] > lhand[-1]

def get_hand_type(hand):
    types = ['A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2']
    values = [0 ,  0 ,  0 ,  0,   0,    0,   0,   0,  0,   0,   0,   0,   0]
    jokers = 0

    for card in hand:
        values[types.index(card)] += 1
        values[types.index('J')] = 0
        if card == 'J':
            jokers += 1

    # add jokers to the count: 
    values[values.index(max(values))] += jokers 

    if values.count(5):
        hand_type = 7
    elif values.count(4):
        hand_type = 6
    elif values.count(3) and values.count(2):
        hand_type = 5
    elif values.count(3):
        hand_type = 4
    elif values.count(2) == 2:
        hand_type = 3
    elif values.count(2) == 1:
        hand_type = 2
    else:
        hand_type = 1

    return hand_type

tic = time.perf_counter()
lines = Path('day07/input.txt').read_text().split('\n')

for index, line in enumerate(lines):
    hand, bid = line.split(' ')
    line += ' ' + str(get_hand_type(hand))
    lines[index] = line

sorted_lines = quicksort(lines)
rank = 1
sum = 0 
for line in sorted_lines:
    hand, bid, hand_type = line.split(' ')
    sum += int(bid)*rank 
    rank += 1

print('Total sum is: ', sum)

toc = time.perf_counter()
print('Time: ', toc-tic, ' seconds')
# get hand types and store in lines as third value of each row
# implement comparing funtion
# call sort function
# sum / add / print res
