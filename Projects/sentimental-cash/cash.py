from cs50 import get_float


counter = 0


while True:
    change = get_float("Change owed: ")
    if change >= 0.0:
        break


change = change * 100
while change > 0:
    if change >= 25:
        change -= 25
        counter += 1
    elif change >= 10:
        change -= 10
        counter += 1
    elif change >= 5:
        change -= 5
        counter += 1
    elif change >= 1:
        change -= 1
        counter += 1


print(counter)