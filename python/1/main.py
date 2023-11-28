import numpy as np

if __name__ == '__main__':
    with open('input.txt','r') as file:
        input = file.read()
    dwarfs = input.split('\n\n')
    dwarfs = list(map(lambda x: x.replace('\n', ' '),dwarfs))
    total = []
    for dwarf in dwarfs:
        foods = dwarf.strip().split(' ')
        total.append(0)
        for food in foods:
            total[-1] += int(food)

    print(f'Maximum calories ({np.amax(total)}) carried by elf {np.argmax(total)}')
