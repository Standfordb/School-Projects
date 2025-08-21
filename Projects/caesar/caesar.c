#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

string encypher(string, int);

const int ALPHABET = 26;


int main(int argc, string argv[])
{

    // Check for correct number of command line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check that argv[1] is in fact an integer
    string cipher = argv[1];
    int cipher_len = strlen(cipher);
    for (int i = 0; i < cipher_len; i++)
    {
        if (!isdigit(cipher[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert cipher string to an integer
    int key = atoi(cipher);

    // Reduce the key to a number between 0-25
    if (key > ALPHABET)
    {
        key %= ALPHABET;
    }


    // Get text and encypher it
    string text = get_string("plaintext: ");
    text = encypher(text, key);
    printf("ciphertext: %s\n", text);
}


// Create a function to encypher text
string encypher(string text, int key)
{
    // Get the length of the text
    int length = strlen(text);

    // Iterate over each character in the text
    for (int i = 0; i < length; i++)
    {
        // If the character is a letter
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            // Increment the character by 1 until we reach the key
            for (int j = 0; j < key; j++)
            {
                text[i] += 1;

                // If we go passed z go back to a
                if (text[i] == '[' || text[i] == '{')
                {
                    text[i] -= ALPHABET;
                }
            }


        }
    }

    return text;
}