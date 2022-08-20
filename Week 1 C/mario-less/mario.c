#include <cs50.h>
#include <stdio.h>


int main(void)
{

// Get Height of staircase
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

// Create the staircase
    // For each column
    for (int i = 1; i <= height ; i += 1)
    {
        // For each row, print the spaces
        for (int j = 0; j < height - i ; j += 1)
        {
            printf(" ");
        }
        // For each row, print the hashes
        for (int j = 0; j < i ; j += 1)
        {
            printf("#");
        }
        printf("\n");
    }
}
