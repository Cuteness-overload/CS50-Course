import csv
import sys


def main():

    # TODO: Check for command-line usage
    if (len(sys.argv) != 3) or (sys.argv[1][-4:] != '.csv') or (sys.argv[2][-4:] != '.txt'):
        print("Usage: python dna.py data.csv sequence.txt")
        return

    # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1]) as rawcsv:
        reader = csv.DictReader(rawcsv)
        for i in reader:
            database.append(dict(i))

    # TODO: Read DNA sequence file into a variable
    dna_sequence = open(sys.argv[2]).read()

    # TODO: Find longest match of each STR in DNA sequence
    # Getting the different DNA subsequences to check from our CSV
    # GeeksforGeeks helped a lot
    dna_subsequence = []
    for k, v in database[1].items():
        dna_subsequence.append(k)
    del dna_subsequence[0]

    # simply checking every sub against the sequence
    # and creating a dictionnary of the results
    result = {}
    for i in range(len(dna_subsequence)):
        longest = longest_match(dna_sequence, dna_subsequence[i])
        result[dna_subsequence[i]] = longest

    # TODO: Check database for matching profiles
    for i in range(len(database)):
        name = database[i].pop('name')

        # changing the values in database to ints
        for k, v in database[i].items():
            database[i][k] = int(v)

        # and now finally, checking against each other
        # saw some stack overflow messages mentioning zip, so went and checked it out
        shared = 0
        for l, j in zip(database[i].items(), result.items()):
            if l == j:
                shared += 1
        if shared == len(result):
            print(name)
            return

    print('No match')
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
