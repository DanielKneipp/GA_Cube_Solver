import re
import argparse

def to_text( sol ):
    for number in sol.split(' '):
        m = ''
        n = int(number)

        if n == -1:
            continue

        level = n // 18
        move_type = (n // 6) % 3
        face = n % 6

        if level != 0:
            m = str(level + 1)

        if face == 0:
            m = m + 'F'
        elif face == 1:
            m = m + 'B'
        elif face == 2:
            m = m + 'U'
        elif face == 3:
            m = m + 'D'
        elif face == 4:
            m = m + 'L'
        elif face == 5:
            m = m + 'R'

        if move_type == 1:
            m = m + '\''
        elif move_type == 2:
            m = m + '2'

        yield m

def to_numeric( sol ):
    pattern = re.compile(r'(\d)?([UDLRFB])([\d\'])?')
    for level, face, move_type in re.findall(pattern, sol):

        m = -1
        if face == 'F':
            m = 0
        elif face == 'B':
            m = 1
        elif face == 'U':
            m = 2
        elif face == 'D':
            m = 3
        elif face == 'L':
            m = 4
        elif face == 'R':
            m = 5

        if(level != ''):
            m = m + 18 * (int(level) - 1)

        if(move_type == '\''):
            m = m + 6
        elif(move_type == '2'):
            m = m + 12

        yield m

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Cube solution representation converter')

    parser.add_argument('solution', type=str, help='Solution string')
    parser.add_argument('--to-numeric', action='store_true', dest='to_numeric', help='Convert to numeric representation')
    parser.add_argument('--to-text', action='store_true', dest='to_text', help='Convert to text representation')

    args = parser.parse_args()

    if args.to_numeric:
        for m in to_numeric(args.solution):
            print(str(m), end=' ')
    elif args.to_text == 1:
        for m in to_text(args.solution):
            print(str(m), end=' ')
    else:
        parser.print_help()
