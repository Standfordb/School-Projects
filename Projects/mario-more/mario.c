#include <cs50.h>
#include <stdio.h>

void draw_pyramid(int);
int get_height();


int main(void)
{
    int height = get_height();
    draw_pyramid(height);
}


//function to ask user for height
int get_height()
{
    int height = 0;
    //ask the user for an input between 1-8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    return height;
}

//function to draw the pyramid
void draw_pyramid(int num)
{
    for (int i = 1; i <= num; i++)
    {
        //add spaces before the first bricks
        for (int j = num - i; j > 0; j--)
        {
            printf(" ");
        }
        //add left side bricks
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        //add middle spaces
        printf("  ");
        //add right side bricks
        for (int l = 0; l < i; l++)
        {
            printf("#");
        }
        //move to next line
        printf("\n");
    }
}