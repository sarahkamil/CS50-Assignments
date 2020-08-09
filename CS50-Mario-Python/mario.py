from cs50 import get_int

height = 0
while height < 1 or height > 8:
    height = get_int("Height: ")


for i in reversed(range(1, height + 1)):
    print((i - 1) * " " + ((height + 1) - i) * "#")