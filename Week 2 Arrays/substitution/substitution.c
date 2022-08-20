#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>


int check_key(string key);
char swap(char base_letter, string key);



int main(int argc, string argv[])
{
    // the main function in function
    // Checks for accuracy then does the swap
    if (argc == 2 && check_key(argv[1]))
    {
        string ptext = get_string("plaintext: ");
        printf("ciphertext: ");

        int length = strlen(ptext);

        // Swap happens here thx to the swap function
        for (int i = 0; i < length ; i++)
        {
            char ctext = swap(ptext[i], argv[1]);
            printf("%c", ctext);
        }
        printf("\n");
        return 0;
    }
    else
    {
        // Message to print when error in initial input
        printf("Usage: ./substitution Key <-(26 letters)\n");
        return 1;
    }

}


// Function checks for any issues with the key
int check_key(string key)
{
    int check = 1;
    // Check length
    if (strlen(key) != 26)
    {
        check = 0;
    }

    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            // Check for duplicated
            if (tolower(key[i]) == tolower(key[j]))
            {
                check = 0;
            }
        }
        // Check for non alphabet symbols
        if (!isalpha(key[i]))
        {
            check = 0;
        }
    }
    return check;
}


// Function which swaps out the letters
char swap(char base_letter, string key)
{
    char swapped_letter = base_letter;

    // Swapping the lowercase letters
    if (islower(base_letter))
    {
        int i = base_letter - 97;
        swapped_letter = key[i];
        swapped_letter = tolower(swapped_letter);
    }
    //Swapping the uppercase letters
    if (isupper(base_letter))
    {
        int i = base_letter - 65;
        swapped_letter = key[i];
        swapped_letter = toupper(swapped_letter);
    }
    // No need to touch the puctuation
    // now return the swapped letter
    return swapped_letter;
}


// Take the character
// subtract either 97 or 65 depending on case
// check what lives at that number in the cypher array
// replace that character with it
