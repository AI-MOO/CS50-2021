from cs50 import get_string
import re

# patterns to detect words, letters and sentences using re module
alphabets = "[a-zA-Z]"
spaces = "[ ]"
end_punctuation = "[!?.]"


def main():
    # propmpt the user for a text
    Text = get_string("Text: ")
    # use grade computer function to calculate the grade level
    grade = grade_computer(Text)
    print(grade)


def grade_computer(Text):

    # counters for leters, words and sentences
    letters_counter, words_counter, sentences_count = 0, 1, 0

    # count number of letters, words, and sentences in the input text
    for i in range(len(Text)):

        if re.search(alphabets, Text[i]):
            letters_counter += 1

        elif re.search(spaces, Text[i]):
            words_counter += 1

        elif re.search(end_punctuation, Text[i]):
            sentences_count += 1

    # calculating the number of letters and sentences per 100 words
    L = letters_counter * 100.0 / words_counter
    S = sentences_count * 100.0 / words_counter
    # computing the grade by Coleman-Liau index formula
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Reading level is under Grade 1
    if index < 1:
        return "Before Grade 1"

    # Reading level is above Grade 16
    if index > 16:
        return "Grade 16+"

    # reading levels between Grade 1 & Grade 16 !
    else:
        return f"Grade {index}"


if __name__ == '__main__':
    main()