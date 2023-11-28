def a_in_b(a, b):
    return int(a[0]) >= int(b[0]) and int(a[1]) <= int(b[1])


def a_overlaps_b(a, b):
    return not (int(a[1]) < int(b[0]) or int(b[1]) < int(a[0]))


if __name__ == '__main__':
    with open('input.txt') as file:
        input = file.read()
    input = input.strip().split('\n')
    input = map(lambda x: x.split(','), input)
    input = map(lambda x: [x[0].split('-'), x[1].split('-')], input)
    input = filter(lambda x: a_overlaps_b(x[0], x[1]), input)
    input = list(input)
    print(len(input))
