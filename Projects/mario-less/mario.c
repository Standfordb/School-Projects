#include <cs50.h>
#include <stdio.h>

void draw_pyramid(int);

int height = 0;


int main(void)
{

    // Get a number between 1-8 from the user
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Draw the pyramid
    draw_pyramid(height);


}


// Create a function to recursively draw a pyramid of a given height
void draw_pyramid(n)
{
    // If at the bottom layer return
    if (n == 0)
    {
        return;
    }

    // Draw the previous layer of the pyramid
    draw_pyramid(n - 1);

    // Draw the spaces before the #'s
    for (int i = n; i < height; i++)
    {
        printf(" ");
    }

    // Draw the #'s
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }

    // Go to the next line
    printf("\n");
}