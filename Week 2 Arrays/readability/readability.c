#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// My functions to clean up the main
int num_letters(string text, int len);
int num_words(string text, int len);
int num_sent(string text, int len);


int main(void)
{
    string text = get_string("Text: ");
    int len = strlen(text);

    // Collect all the necessary info
    float letters = num_letters(text, len);
    float words = num_words(text, len);
    float sent = num_sent(text, len);

    // Coleman-Liau index
    float L = letters / words * 100;
    float S = sent / words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print the result
    // Result higher than 15
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    // Result lower than 1
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        // Any normal grade
        printf("Grade %i\n", index);
    }
}


// Find the number of letters in the text
int num_letters(string text, int len)
{
    int letters = 0;
    for (int i = 0, n = len; i < n; i++)
    {
        // detect a letter
        if (isalpha(text[i]))
        {
            letters += 1;
        }
    }
    return letters;
}

// Find the number of words in the text
int num_words(string text, int len)
{
    int words = 1;
    for (int i = 0, n = len; i < n; i++)
    {
        // Detect a space
        if (isspace(text[i]))
        {
            words += 1;
        }
    }
    return words;
}

// Find the number of sentences in the text
int num_sent(string text, int len)
{
    int sent = 0;
    for (int i = 0, n = len; i < n; i++)
    {
        // Find the symbols that indicate end of sentence
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sent += 1;
        }
    }
    return sent;
}