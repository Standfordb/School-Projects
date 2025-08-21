#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string make_lower(string);
string get_key(string);
string encipher(string, string);

//declare global variables
int alpha_lower [26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int alpha_upper [26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int array_size = sizeof(alpha_lower) / sizeof(int);//get size of the array


int main(int argc, string argv[])
{

    //check for correct number of command line arguments
    if (argc != 2)
    {
        printf("Error 1: Missing KEY\nUsage: ./substitution KEY\n");
        return 1;
    }

    //check for proper length of KEY
    int len = strlen(argv[1]);
    if (len != 26)
    {
        printf("Error 2: KEY must be 26 characters long\n");
        return 1;
    }

    //chech that KEY only uses letters
    string s_low = make_lower(argv[1]);//convert KEY to all lowercase
    for (int i = 0; i < len; i++)
    {
        if (s_low[i] < 'a' || s_low[i] > 'z')
        {
            printf("Error 3: KEY uses non alphabetic characters\n");
            return 1;
        }
    }

    //check that KEY has no duplicate letters
    for (int k = 0; k < len; k++)
    {
        for (int j = k + 1; j < len; j++)
        {
            if (s_low[k] == s_low[j])
            {
                printf("Error 4: Must not contain duplicate characters\n");
                return 1;
            }
        }
    }



    string plain_text = get_string("plaintext: ");//ask for input
    string key = get_key(argv[1]);//calculate cipher key
    string cipher_text = encipher(plain_text, key);//apply cipher to text
    printf("ciphertext: %s\n", cipher_text);//output enciphered text

    return 0;

}


//calculate the cipher key
string get_key(string s)
{
    string key = s;
    int l = strlen(s);

    for (int i = 0; i < l; i++)
    {
        key[i] = s[i] - alpha_lower[i];//subtract corresponding alphabet character from key character
    }

    return key;
}


//apply the cipher
string encipher(string s, string key)
{
    int l = strlen(s);

    for (int i = 0; i < l; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))//check that character is a letter
        {
            for (int k = 0; k < array_size; k++)
            {
                if (s[i] == alpha_lower[k] || s[i] == alpha_upper[k])//check which letter character is
                {
                    s[i] = s[i] + key[k];//shift letter by cipher key
                    k = 26;
                }
            }
        }
    }

    return s;
}


//convert string to lowercase
string make_lower(string s)
{
    int l = strlen(s);
    for (int i = 0; i < l; i++)//for each letter in string
    {
        s[i] = tolower(s[i]);//make lowercase
    }

    return s;
}