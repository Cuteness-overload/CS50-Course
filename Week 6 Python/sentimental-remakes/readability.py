from cs50 import get_string

# Defining the function to find the number of letters


def num_letters(text):
    letters = 0
    for char in text:
        if char.isalpha() == True:
            letters += 1
    return letters

# Defining the function to find the number of words


def num_words(text, length):
    words = 1
    for i in range(length):
        if text[i] == " ":
            words += 1
    return words

# Defining the function to find the number of sentences.


def num_sentences(text, length):
    sent = 0
    for i in range(length):
        # Membership test with iterables thx www.towardsdatascience.com
        if text[i] in [".", "!", "?"]:
            sent += 1
    return sent


# Main function
while True:
    # Getting user input
    text = get_string("Text: ")

    # finding the string's length
    length = len(text)
    # finding the number of leters, words and sentences
    letters = num_letters(text)
    words = num_words(text, length)
    sent = num_sentences(text, length)

    # calculating the index
    L = letters / words * 100
    S = sent / words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Sending the appropriate message to the grade
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")
    break

