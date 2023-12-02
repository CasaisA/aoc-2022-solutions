import numpy as np


def move(number, origin, destination):
    for n in range(number):
        destination.append(origin.pop())


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        input = file.read()
    input = input.split('\n')
    stack_data = input[:8]
    # setup the stacks
    stacks = [[] for i in range(9)]
    for i in range(9):  # number of stacks
        j = 4*i + 1
        for s in reversed(range(8)):
            if j < len(stack_data[s]):
                appender = stack_data[s][j]
                if appender != ' ':
                    stacks[i].append(appender)
    rules = input[10:-1]
    rules = map(lambda x: x.strip().split(' '), rules)
    rules = map(lambda x: [int(x[i]) for i in (1, 3, 5)], rules)
    for rule in rules:
        move(rule[0], stacks[rule[1]-1], stacks[rule[2]-1])
    result = ''
    for s in stacks:
        result += s[-1]
    print(result)
