from cs50 import get_int

nbr = get_int('Number: ')
while (nbr <= 0):        # Loop until wrong conditions
    nbr = get_int('Number: ')

qty_digits = 0
tmp = nbr
odd = 0
sum = 0
while (tmp > 0):
    qty_digits += 1
    app = tmp % 10
    if (odd == 1):
        odd = 0
        if (app < 5):
            sum += 2 * app
        else:
            sum += 1 + (app - 5) * 2
    else:
        sum += app
        odd = 1
    tmp //= 10
if (sum % 10 == 0 and qty_digits == 15 and ((nbr >= 340000000000000 and nbr < 349999999999999) or (nbr >= 370000000000000 and nbr < 379999999999999))):
    print("AMEX")
elif (sum % 10 == 0 and qty_digits == 16 and (nbr >= 5100000000000000 and nbr < 5599999999999999)):
    print("MASTERCARD")
elif (sum % 10 == 0 and (qty_digits == 13 or qty_digits == 16) and ((nbr >= 400000000000000 and nbr < 4999999999999999) or (nbr >= 400000000000 and nbr < 4999999999999))):
    print("VISA")
else:
    print("INVALID")
