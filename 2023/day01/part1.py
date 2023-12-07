from pathlib import Path

def find_first_number(line):
    res = 'A'
    for char in line:
        if char.isnumeric():
            res = char
            break
    return res
        
def find_last_number(line):
    line = line[::-1]
    res = 'A'
    for char in line:
        if char.isnumeric():
            res = char
            break
    return res

txt = Path('input1.txt').read_text()
lines = txt.split('\n')
numbers = []
sum = 0

for line in lines:
    num1 = find_first_number(line)
    num2 = find_last_number(line)
    if num1.isnumeric() and num2.isnumeric():
        numbers.append(int(num1 + num2))
        sum += int(num1 + num2)

print(numbers)
print(sum)
