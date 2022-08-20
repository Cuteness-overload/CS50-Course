# TODO
from cs50 import get_int

# getting the height from the user
height = 0
while height < 1 or height > 8:
    height = get_int("Height: ")

# printing out the staircase
for i in range(height):
    blocks = "#" * (i + 1)
    space = " " * (height - (i + 1))
    print(f"{space}{blocks}  {blocks}")