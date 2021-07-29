from cs50 import get_float


# prompt the user to enter the change owed


def main():
    dollars = 0.0
    while (dollars > 0.0) == False:
        dollars = get_float("Change owed: ")

    cents = round(dollars * 100)
    coins_number = coins(cents)
    print(coins_number)

# check the number of returned coins according to greedy algorthim


def coins(cents):
    counter = 0
    # 25 cents loop
    while (cents >= 25):
        cents = cents - 25
        counter += 1
    # 10 cents loop
    while (cents >= 10):
        cents = cents - 10
        counter += 1
    # 5 cents loop
    while (cents >= 5):
        cents = cents - 5
        counter += 1

    # 1 cent loop
    while (cents >= 1):
        cents = cents - 1
        counter += 1
    return counter


if __name__ == "__main__":
    main()