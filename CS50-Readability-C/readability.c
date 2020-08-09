#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

bool isLetter(char x);
bool isPunctuation(char x);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    //printf("You entered: %s \n", text);
    int num_letters = count_letters(text);
    //printf("The text has %i letters. \n", num_letters);
    int num_words = count_words(text);
    //printf("The text has %i words. \n", num_words);
    int num_sentences = count_sentences(text);
    //printf("The text has %i sentences. \n", num_sentences);

    float L = (100.0 * num_letters / num_words);
    float S = (100.0 * num_sentences / num_words);
    float index = round((0.0588 * L) - (0.296 * S) - 15.8);
    int i = (int)index;

    //printf("%i \n", i);

    if (i >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (i < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", i);
    }
}

int count_letters(string text)
{
    int num_letters = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isLetter(text[i]))
        {
            num_letters++;
        }
    }
    return num_letters;
}

int count_words(string text)
{
    if (strlen(text) == 0)
    {
        return 0;
    }
    int num_spaces = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ' && text[i - 1] != ' ')
        {
            num_spaces++;
        }
    }
    return num_spaces + 1;
}

int count_sentences(string text)
{
    int num_sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isPunctuation(text[i]) && !isPunctuation(text[i - 1]))
        {
            num_sentences++;
        }
    }
    return num_sentences;
}



bool isLetter(char x)
{
    char alphabet_array[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 52; i++)
    {
        if (alphabet_array[i] == x)
        {
            return true;
        }
    }
    return false;
}

bool isPunctuation(char x)
{
    char punctuation_array[] = {'!', '?', '.'};
    for (int i = 0; i < 3; i++)
    {
        if (punctuation_array[i] == x)
        {
            return true;
        }
    }
    return false;
}

