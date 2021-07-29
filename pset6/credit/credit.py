from cs50 import get_int
import math


def main():
    # prompt the user a credit card number CC
    CC = 0
    while (CC <= 0):
        CC = get_int("Number: ")

    # convert CC to string to obtain the length of number
    CC_string = str(CC)
    length_of_CC = len(CC_string)

    #validity = check_validity(length_of_CC, CC)
    # Considering CC has a valid number by Luhn’s Algorithm
    validity = True

    if validity == True:
        card_type = check_card_type(CC_string)
        print(card_type)
    else:
        print("INVALID")


# Extra Work: check if the number is valid by Luhn’s Algorithm
'''
def check_validity(length_of_CC, CC):
    sum1, sum2, total, digit_check = 0, 0, 0, False
    for i in range(length_of_CC + 1):

        if digit_check == False:
            sum1 = sum1 + (CC % 10)
            CC = math.floor(CC / 10 )
            digit_check = True

        elif digit_check == True:
            temp = 2 * (CC % 10)
            if temp >= 10:
                sum2 = sum2 + round(temp % 10 + temp / 10)
            else:
                sum2 = sum2 + temp

            CC = math.floor(CC / 10 )
            digit_check = False

    total = sum1 + sum2
    if total % 10 == 0:
        return True

    else:
        return False
'''


def check_card_type(CC_string):

    # obtain firts digit and second digit to check the type of card
    First_digit = int(CC_string[0])
    First_2_digits = int(CC_string[0]) * 10 + int(CC_string[1])

    # American Express
    print(First_digit, First_2_digits)
    if First_2_digits in [34, 37]:
        return "AMEX"

    # MASTERCARD
    elif First_2_digits in [51, 52, 53, 54, 55]:
        return "MASTERCARD"

    # VISA Card
    elif First_digit == 4:
        return "VISA"

    else:
        return "INVALID"


if __name__ == "__main__":
    main()