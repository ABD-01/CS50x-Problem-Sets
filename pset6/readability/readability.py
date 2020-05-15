from cs50 import get_string


def main():
    text = get_string("Text: ")
    L = count_letters(text) / count_words(text) * 100
    S = count_sentences(text) / count_words(text) * 100
    index = (0.0588 * L) - (0.296 * S) - 15.8
    grade = int(round(index))

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def count_letters(text):
    count = 0
    for i in text:
        if i.isalpha():
            count += 1
    return count


def count_words(text):
    count = 1
    for i in text:
        if i.isspace():
            count += 1
    return count


def count_sentences(text):
    count = 0
    ending = [".", "?", "!"]
    for i in text:
        if i in ending:
            count += 1
    return count


main()

