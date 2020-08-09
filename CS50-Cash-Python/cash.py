from cs50 import get_float

change = -1
while change < 0:
    change = get_float("Change owed: ")

change = change*100

coins = 0
while change > 0:
    if change >= 25:
        coins += 1
        change -= 25
        continue
    elif change >= 10:
        coins += 1
        change -= 10
        continue
    elif change >= 5:
        coins += 1
        change -= 5
        continue
    elif change >= 1:
        coins += 1
        change -= 1

print(coins)