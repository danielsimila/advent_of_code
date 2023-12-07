from pathlib import Path

txt = Path('day02/input.txt').read_text()
games = txt.split('\n')

no_red = 12
no_green = 13
no_blue = 14
sum = 0

for game in games:
    [game_no, result] = game.split(':')
    game_no = int(game_no[5::])

    turns = result.split(';')
    valid = 1
    for turn in turns:
        types = turn.split(',')
        for type in types:
            if type.find('red') != -1:
                no = int(type.replace(' red','').strip())
                if no > no_red:
                    valid = 0
            if type.find('green') != -1:
                no = int(type.replace(' green','').strip())
                if no > no_green:
                    valid = 0
            if type.find('blue') != -1:
                no = int(type.replace(' blue','').strip())
                if no > no_blue:
                    valid = 0
                

    if valid:
        sum += game_no

print(sum)
