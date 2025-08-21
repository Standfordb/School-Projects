import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence,txt")
        exit()

    # Read database file into a variable
    people = get_people(sys.argv[1])

    # Read DNA sequence file into a variable
    sequence = get_sequence(sys.argv[2])

    # Find longest match of each STR in DNA sequence
    subsequence = get_subsequence(sys.argv[1])
    dna = get_dna(subsequence, sequence)

    # Check database for matching profiles
    print_match(people, dna)
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


def get_people(file):
    people = []
    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            people.append(row)

    return people


def get_sequence(file):
    with open(sys.argv[2], 'r') as file:
        reader = csv.reader(file)
        sequence = next(reader)

    return sequence[0]


def get_subsequence(file):
    subsequence = []
    with open(sys.argv[1], 'r') as file:
        reader = csv.reader(file)
        subsequence = next(reader)
        subsequence.pop(0)

    return subsequence


def get_dna(subsequence, sequence):
    dna = {}
    idx = 0
    for str in subsequence:
        dna[subsequence[idx]] = 0
        idx += 1

    for str in subsequence:
        dna[str] = longest_match(sequence, str)

    return dna


def match_dna(person, dna):
    for str in dna:
        if dna[str] != int(person[str]):
            return False

    return True


def print_match(people, dna):
    for person in people:
        if match_dna(person, dna) == True:
            print(person["name"])
            return

    print("No match.")
    return


main()
