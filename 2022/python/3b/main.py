import numpy as np


def get_byte_hex(input):
    output = input.encode('utf-8').hex()
    return int(f"{output}", base=16)


if __name__ == '__main__':
    mybyte = get_byte_hex('a') & get_byte_hex('b')
    with open('input.txt', 'r') as file:
        input = file\
            .read()\
            .strip()\
            .split('\n')
    input = np.array(input).reshape(int(len(input)/3),3).tolist()
    input = filter(lambda x: set(x[0]) & set(x[1]) & set(x[2]) != set(), input)
    input = map(lambda x: list(set(x[0]) & set(x[1]) & set(x[2])), input)
    input = np.array(list(input)).flatten()
    input = map(get_byte_hex, input)
    input = map(lambda x:  x-get_byte_hex('a') + 1 if x >= get_byte_hex('a')
                else x-get_byte_hex('A') + 27, input)

    input = list(input)
    input = sum(input)
    print(input)
