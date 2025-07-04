from cs50 import get_string
import string


def main():
    text = get_string("Text: ")

    letters = 0
    words = 0
    sentences = 0
    for i, letter in enumerate(text):
        if letter.isalpha():
            letters += 1
        elif letter in string.punctuation or letter.isspace():
            if letter in ['?', '!', '.']:
                words += 1
                sentences += 1
            elif letter in [' ', ',']:
                if text[i - 1].isalpha():
                    words += 1
    index = compute_grade(letters, words, sentences)
    print_output(index)


def compute_grade(letters, words, sentences):
    L = letters / words * 100
    S = sentences / words * 100

    return round(0.0588 * L - 0.296 * S - 15.8)


def print_output(index):
    if index < 1:
        print("Before Grade: 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()
