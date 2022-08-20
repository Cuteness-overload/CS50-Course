#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

// Create the pyramid
    // For each row
    for (int i = 1; i <= height ; i += 1)
    {
        // Creating the air
        for (int j = 0; j < height - i ; j += 1)
        {
            printf(" ");
        }
        // Creating the first staircase
        for (int j = 0; j < i ; j += 1)
        {
            printf("#");
        }
        // Creating the gap
        printf("  ");
        // Creating the second staircase
        for (int j = 0; j < i ; j += 1)
        {
            printf("#");
        }
        // Skip to the next row
        printf("\n");
    }
}
