#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get card number
    long card = get_long("Number: ");

    // Find card length
    long card_copy = card;
    int length = ! 1;
    while (card_copy)
    {
        length += 1;
        card_copy /= 10;
    }

    // Create an Array for all the digits
    // Array is already flipped on creation :)
    int digits[length];
    long card_copy2 = card;
    for (int i = 0; i < length; i++)
    {
        int digit = card_copy2 % 10;
        card_copy2 = card_copy2 / 10;
        digits[i] = digit;
    }

    //Every second digit of the array is multiplied by two
    //The resulting digits are added together
    int sum_mult = 0;
    for (int i = 1; i < length; i += 2)
    {
        int post_mult = digits[i] * 2;

        // Calculate the length of the resulting numbers (post_mult)
        long post_mult_copy = post_mult;
        int post_mult_l = ! 1;
        while (post_mult_copy)
        {
            post_mult_l += 1;
            post_mult_copy /= 10;
        }

        // Calculate the sum of the digits of the resulting numbers
        for (int j = 0; j < post_mult_l; j++)
        {
            int mult_dig = post_mult % 10;
            sum_mult += mult_dig;
            post_mult = post_mult / 10;
        }
    }

    // Other digits are summed to the total
    for (int i = 0; i < length; i += 2)
    {
        int no_mult = digits[i];
        sum_mult += no_mult;
    }

    // Check if it ends with a zero
    // Changing the checksum status accordingly
    string status = "INVALID";
    if (sum_mult % 10 == 0)
    {
        // Choosing which card it is
        // Finding the first two numbers of the card
        long start_num = card;
        while (start_num > 100)
        {
            start_num = start_num / 10;
        }

        // Checking if it's an AMEX
        if (start_num == 34 || start_num == 37)
        {
            if (length == 15)
            {
                status = "AMEX";
            }
        }
        // Checking if it's a Mastercard
        else if (start_num == 51 || start_num == 52 || start_num == 53 || start_num == 54 || start_num == 55)
        {
            if (length == 16)
            {
                status = "MASTERCARD";
            }
        }
        // Checking if it's a VISA
        else
        {
            start_num = start_num / 10;
        }
        if (start_num == 4)
        {
            if (length == 13 || length == 16)
            {
                status = "VISA";
            }
        }
    }
    // Printing final outcome.
    printf("%s\n", status);
}