import cs50


def main():
    height = 0
    # higeht should be between 1 & 8 otherwise reprompt
    while (height >= 1 and height <= 8) == False:
        height = get_height()

    for i in range(height):
        print((height - i - 1) * " ", end="")
        print((i+1) * "#")


def get_height():
    blocks = cs50.get_int("height: ")
    return blocks


if __name__ == "__main__":
    main()

