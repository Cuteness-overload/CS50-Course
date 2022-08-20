from cs50 import get_int

# get a valid string of digits
card = 0
while card < 1:
    card = get_int("Number: ")

# Converting a number into a list of digits
# thx to /www.quizcure.com for this (list comprehensions sound amazing)
cardnums = [int(digits) for digits in str(card)]

# find number length
length = len(cardnums)

# LUHN'S ALGO

# multiplying by two
sum_mult = 0
startmult = length % 2
startadd = (length + 1) % 2

# start changes based on even or odd length
for i in range(startmult, length, 2):
    post_mult = cardnums[i] * 2
    digi_mult = [int(digits) for digits in str(post_mult)]
    # adding up the seperate digits of a number
    for i in range(len(digi_mult)):
        sum_mult += digi_mult[i]

# adding the other numbers
for i in range(startadd, length, 2):
    sum_mult += cardnums[i]

# figuring out if the card is valid or not
# setting my initial values
# list slicing to the rescue to get first to nums of the card
status = "INVALID"
start_nums = int(str(card)[:2])

if sum_mult % 10 == 0:
    if start_nums == 34 or start_nums == 37 and length == 15:
        status = "AMEX"
    elif start_nums in range(51, 56) and length == 16:
        status = "MASTERCARD"
    else:
        start_nums = start_nums / 10
        if start_nums == 4 and length == 13 or length == 16:
            status = "VISA"

print(status)