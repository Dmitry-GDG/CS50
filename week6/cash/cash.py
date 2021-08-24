from cs50 import get_float

dollars = get_float('Change owed: ')
while (dollars <= 0):        # Loop until wrong conditions
    dollars = get_float('Change owed: ')
cents = int(dollars * 100)
outp = 0
while (cents - 25 * outp >= 25):
    outp += 1
cents -= 25 * outp
if (cents >= 20):
    outp += 2
    cents -= 20
elif (cents >= 10):
    outp += 1
    cents -= 10
if (cents >= 5):
    outp += 1
    cents -= 5
outp += cents
print(outp)