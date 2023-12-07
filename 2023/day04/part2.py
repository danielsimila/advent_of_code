from pathlib import Path
from numpy import ones

lines = Path('input.txt') 
lines = lines.read_text().split('\n')
scratchcards = ones(len(lines), dtype=int)

for index, line in enumerate(lines):
    game_info, game = line.split(':')
    winning_numbers, numbers = game.split('|')
    numbers = numbers.strip().split(' ')
    winning_numbers = winning_numbers.strip().split(' ')

    card_score = 0
    for number in numbers:
        if number != '' and winning_numbers.count(number) >= 1:
            card_score += 1
    
    if card_score != 0:
        for i in range(card_score):
            scratchcards[index+i+1] += scratchcards[index]

print(scratchcards.sum())
