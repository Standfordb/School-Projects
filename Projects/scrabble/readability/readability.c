#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

float count_letters(string);
float count_words(string);
float count_sent(string);
void get_grade(int);

int main(void)
{
    string text = get_string("Text: ");
    float words = count_words(text);
    float letters = count_letters(text);
    float sent = count_sent(text);

    //compute Coleman_Liau index
    float L = letters / words * 100;
    float S = sent / words * 100;
    float grade = 0.0588 * L - 0.296 * S - 15.8;
    int final_grade = round(grade);//round to nearest integer

    //print final grade level
    get_grade(final_grade);


}

//count the letters in the text
float count_letters(string t)
{
    int len = strlen(t);
    int count = 0;

    for (int i = 0; i < len; i++)
    {
        if ((t[i] >= 'A' && t[i] <= 'Z') || (t[i] >= 'a' && t[i] <= 'z'))
        {
            count++;
        }
    }
    return count;
}

//count the words in the text
float count_words(string t)
{
    int len = strlen(t);
    int count = 0;

    for (int i = 0; i < len; i++)
    {
        if (t[i] == 32)
        {
            count++;
        }
    }
    return count + 1;
}

//count the sentences in the text
float count_sent(string t)
{
    int len = strlen(t);
    int count = 0;

    for (int i = 0; i < len; i++)
    {
        if (t[i] == '.' || t[i] == '?' || t[i] == '!')
        {
            count++;
        }
    }
    return count;
}

//print the grade level
void get_grade(int n)
{
    if (n >= 1 && n <= 15)
    {
        printf("Grade %i\n", n);
    }
    else if (n < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}