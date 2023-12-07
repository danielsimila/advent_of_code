from pathlib import Path

txt = Path('day02/input.txt').read_text()
games = txt.split('\n')

sum = 0

for game in games:
    [game_no, result] = game.split(':')
    game_no = int(game_no[5::])

    max_red = 0
    max_green = 0
    max_blue = 0

    turns = result.split(';')
    for turn in turns:
        types = turn.split(',')
        for type in types:
            if type.find('red') != -1:
                no = int(type.replace(' red','').strip())
                if no > max_red:
                    max_red = no
            if type.find('green') != -1:
                no = int(type.replace(' green','').strip())
                if no > max_green:
                    max_green = no
            if type.find('blue') != -1:
                no = int(type.replace(' blue','').strip())
                if no > max_blue:
                    max_blue = no                

    sum += max_red * max_green * max_blue

print(sum)
