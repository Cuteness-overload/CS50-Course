#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks for the user's name
    string name = get_string("What's your name? ");

    // Says hello to the user
    printf("hello, %s\n", name);
}