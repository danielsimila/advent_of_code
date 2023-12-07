from pathlib import Path

lines = Path('input.txt') 
lines = lines.read_text().split('\n')

sum = 0
for line in lines:
    game_info, game = line.split(':')
    winning_numbers, numbers = game.split('|')
    numbers = numbers.strip().split(' ')
    winning_numbers = winning_numbers.strip().split(' ')

    card_score = 1/2
    for number in numbers:
        if number != '' and winning_numbers.count(number) >= 1:
            card_score *= 2
    
    if card_score < 1:
        card_score = 0

    sum += int(card_score)
            
print(sum)
