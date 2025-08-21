from cs50 import get_int

# Ask user for height only continuing when input is a number between 1 nad 8
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# Print the pyramid
for x in range(1, height + 1):
    print((" " * (height - x)) + ("#" * x) + "  " + ("#" * x))