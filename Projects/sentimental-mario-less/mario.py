from cs50 import get_int


# Get and integer from the user between 1-8
while True:
    height = get_int("Height: ")
    if height > 0 and height <= 8:
        break


# Create a fucntion to recursively draw the pyramid
def draw_pyramid(n):
    if n == 0:
        return

    draw_pyramid(n - 1)

    print(f" " * (height - n) + "#" * n)


# Dray the pyramid
draw_pyramid(height)