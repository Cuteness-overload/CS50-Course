from cs50 import get_float

# Initializing values
amount = -1
quarter = 0.25
dime = 0.10
nickel = 0.05
penny = 0.01

# getting user input
while amount < 0:
    amount = get_float("Change owed: ")

# calc of quarters
quarters = int(amount / quarter)
amount = round(amount - quarters * quarter, 10)
# calc of dimes
dimes = int(amount / dime)
amount = round(amount - dimes * dime, 10)
# calc of nickels
nickels = int(amount / nickel)
amount = round(amount - nickels * nickel, 10)
# pennies
pennies = int(amount / penny)

coins = quarters + dimes + nickels + pennies
print(coins)

# round was needed due to floating point imprecision messing everything up