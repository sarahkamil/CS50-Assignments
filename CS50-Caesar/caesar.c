#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

bool isNumber(string x);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }

    int key;
    string key_string = argv[1];
    if (isNumber(key_string))
    {
        key = atoi(key_string);
    }
    else
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                char shift_up = plaintext[i] - 65;
                char cipher = (shift_up + key) % 26;
                char shift_down = cipher + 65;
                printf("%c", shift_down);
            }
            else
            {
                char shift_up = plaintext[i] - 97;
                char cipher = (shift_up + key) % 26;
                char shift_down = cipher + 97;
                printf("%c", shift_down);
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}

bool isNumber(string x)
{
    for (int i = 0; i < strlen(x); i++)
    {
        if (!isdigit(x[i]))
        {
            return false;
        }
    }
    return true;
}