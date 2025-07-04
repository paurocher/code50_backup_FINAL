def get_int():
    while True:
        print("Number: ", end="")
        number = input()
        try:
            return int(number)
        except ValueError:
            print("Number must be a number.")


def validate_card(number):
    is_pair = False
    pairs = 0
    odds = 0
    number_length = 0

    while number > 0:
        number_length += 1
        num = number % 10  # last digit
        number = number // 10  # remove last digit

        if is_pair:
            doubled = num * 2
            if doubled > 9:
                pairs += doubled % 10
                doubled = doubled // 10
            pairs += doubled
        else:
            odds += num
        is_pair = not is_pair

    if number_length not in [13, 15, 16]:
        print("INVALID")
        return False

    result = pairs + odds

    if result % 10 == 0:
        return True
    else:
        print("INVALID")
        return False


def get_card_company(number):
    header = number
    number_length = 2

    while header > 99:
        number_length += 1
        header = header // 10

    if header in [34, 37]:
        if number_length == 15:
            print("AMEX")
        else:
            print("INVALID")
    elif header >= 51 and header <= 55:
        if number_length == 16:
            print("MASTERCARD")
        else:
            print("INVALID")
    elif header // 10 == 4:
        if number_length in [13, 16]:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


def main():
    number = get_int()
    if validate_card(number):
        get_card_company(number)


main()
