#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int only_digits(string key);
char rotate(char text, int key);


int main(int argc, string argv[])
{
    // Checks if the user correctly inputs the key
    if (argc == 2 && only_digits(argv[1]))
    {
        // Transforms the key into an int
        int c_key = atoi(argv[1]);
        // ask for the text to change
        string pre_ciph = get_string("plaintext: ");
        // print the start of the answer
        printf("ciphertext: ");

        for (int i = 0; i < strlen(pre_ciph); i++)
        {
            char ciph_c = rotate(pre_ciph[i], c_key);
            printf("%c", ciph_c);
        }
        printf("\n");
    }
    // Tell the user how to correctly use the program
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

}




// Checks that the key only contains numbers
int only_digits(string key)
{
    int pass = 1;
    int length = strlen(key);
    for (int i = 0; i < length; i++)
    {
        pass = isdigit(key[i]);
        if (pass == 0)
        {
            break;
        }
    }
    return pass;
}

// Rotates the text by n digits based on the key
char rotate(char text, int key)
{
    char ciph = 'Z';
    if (islower(text))
    {
        ciph = (((text - 97) + key) % 26) + 97;

    }
    else if (isupper(text))
    {
        ciph = (((text - 65) + key) % 26) + 65;
    }
    else
    {
        ciph = text;
    }
    return ciph;
}