from cs50 import get_string


def main():

    text = get_string("Text: ")
    letters = get_letters(text)
    words = get_words(text)
    sentences = get_sentences(text)
    grade = get_grade(letters, words, sentences)
    print_grade(grade)


def get_letters(text):
    letters = 0
    for char in text:
        if char.isalpha() == True:
            letters += 1

    return letters


def get_words(text):
    words = 0
    for char in text:
        if char == " ":
            words += 1
    words += 1

    return words


def get_sentences(text):
    sentences = 0
    for char in text:
        if char == "." or char == "!" or char == "?":
            sentences += 1

    return sentences


def get_grade(letters, words, sentences):
    l = letters / words * 100
    s = sentences / words * 100
    grade = 0.0588 * l - 0.296 * s - 15.8
    grade = round(grade)

    return grade


def print_grade(grade):
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")


if __name__ == "__main__":
    main()