#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name? ");// Gets user name as input
    printf("hello, %s \n", name);//Prints users name!
}