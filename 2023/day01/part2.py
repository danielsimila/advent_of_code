from pathlib import Path

def find_first_number(line, targets):
    res = 'ERROR'
    res_idx = 1e9
    for index, target in enumerate(targets):
        idx = line.find(target)
        if idx != -1 and idx < res_idx:
            res_idx = idx
            if target.isnumeric():
                res = target
            else:
                res = targets[index-10]
    return res
        
def find_last_number(line, targets):
    res = 'ERROR'
    res_idx = -1
    for index, target in enumerate(targets):
        idx = line.rfind(target)
        if idx != -1 and idx > res_idx:
            res_idx = idx
            if target.isnumeric():
                res = target
            else:
                res = targets[index-10]
    return res

txt = Path('input.txt').read_text()
lines = txt.split('\n')

targets = ['0','1','2','3','4','5','6','7','8','9','zero','one','two','three','four','five','six','seven','eight','nine']
numbers = []
sum = 0

for line in lines:
    num1 = find_first_number(line, targets)
    num2 = find_last_number(line, targets)
    if num1.isnumeric() and num2.isnumeric():
        numbers.append(int(num1 + num2))
        sum += int(num1 + num2)

print(numbers)
print(sum)
