from cs50 import get_int

c = get_int('Height: ')
while (c < 1 or c > 8):        # Loop until wrong conditions
    c = get_int('Height: ')

for i in range(1, c+1):
    j = c-i
    while(j > 0):
        print(' ', end='')
        j -= 1
    j = i
    while(j > 0):
        print('#', end='')
        j -= 1
    i += 1
    print('\n', end='')
