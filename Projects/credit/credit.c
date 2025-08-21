#include <stdio.h>
#include <cs50.h>

int get_sum_even(long);
int get_sum_odd(long);
int get_length(long);
int get_company(long);
bool check_valid(int, int, int, int);
void print_response(bool, int);


int main(void)
{
    const long cc_number = get_long("CC Number: "); //promt user for cc number
    int sum_even = get_sum_even(cc_number); //get sum of even digits * 2
    int sum_odd = get_sum_odd(cc_number); //get sum of odd digits
    int cc_length = get_length(cc_number); //get length of cc number
    int cc_company = get_company(cc_number); //match first 2 digits to cc company
    bool cc_valid = check_valid(cc_length, cc_company, sum_odd, sum_even); //check all paramaters for valid cc number

    //output cc company
    print_response(cc_valid, cc_company);
}





//function to get the sum of even digits * 2
int get_sum_even(long num)
{
    int sum = 0;
    int x = 0;
    num /= 10;

    //multiply digits by 2 and get sum
    while (num / 10 > 0)
    {
        x = num % 10;
        x *= 2;
        if (x >= 10)
        {
            x = x % 10;
            x++;
        }
        sum += x;
        num /= 100;
    }

    //one more time for final digit
    x = num;
    x *= 2;
    if (x >= 10)
    {
        x = x % 10;
        x++;
    }

    sum += x;
    return sum;
}

//function to get sum of odd digits
int get_sum_odd(long num)
{
    int sum = 0;

    //get sum of odd digits
    while (num / 10 > 0)
    {
        sum += num % 10;
        num /= 100;
    }

    //one more time for final digit
    sum += num % 10;
    return sum;
}


//function to get length of cc number
int get_length(long num)
{
    int length = 1;

    //calculate length
    while (num / 10 > 0)
    {
        length++;
        num /= 10;
    }

    return length;
}

//function to match first 2 digits of cc number to cc company
int get_company(long num)
{
    int company;

    while (num / 10 >= 20)
    {
        num /= 10;
    }

    if (num == 34 || num == 37)
    {
        company = 1;
    }
    else if (num == 51 || num == 52 || num == 53 || num == 54 || num == 55)
    {
        company = 2;
    }
    else if (num / 10 == 4)
    {
        company = 3;
    }
    else
    {
        company = 0;
    }

    return company;
}

//function to check the validity of the cc number
bool check_valid(int x, int y, int o, int e)
{
    bool valid = true;
    //check the length of the cc number
    if (x != 13 && x != 15 && x != 16)
    {
        valid = false;
    }

    //check the first 1-2 digits of the cc number
    if (y == 0)
    {
        valid = false;
    }

    //check the luhn's algorithm
    if ((o + e) % 10 != 0)
    {
        valid = false;
    }

    return valid;
}


//function to output cc company
void print_response(bool x, int comp)
{
    if (x == false)
    {
        printf("INVALID\n");
    }
    else if (x == true)
    {
        if (comp == 1)
        {
            printf("AMEX\n");
        }
        else if (comp == 2)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("VISA\n");
        }
    }
}