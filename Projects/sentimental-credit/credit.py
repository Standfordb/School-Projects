from cs50 import get_string


def main():

    # Ask user for credit card number ensuring correct length
    number = get_string("Number: ")
    if len(number) != 13 and len(number) != 15 and len(number) != 16:
        print("INVALID")
        exit()

    # Check the Luhn's algorithm of the cc number
    valid = check_valid(number)
    if valid == False:
        print("INVALID")
        exit()

    # Check for credit card company
    company = check_company(number)
    print(company)


def check_valid(number):
    sum = 0
    idx = len(number)

    # Sum the odd digits with the digits of the product of the even digits * 2
    for x in number:
        if idx % 2 == 0:
            x = int(x) * 2
            if x >= 10:
                sum += 1
                x %= 10
            sum += x
        else:
            sum += int(x)
        idx -= 1

    # Confirm the modulus of the sum equals 0
    valid = False
    if sum % 10 == 0:
        valid = True

    return valid
    

def check_company(number):
    # Reduce the number to its first 2 digits
    number = int(number)
    while number / 10 >= 10:
        number = number / 10
    number = int(number)

    # Check digits against credit card companies starting digits
    if number == 34 or number == 37:
        company = "AMEX"
    elif number > 50 and number < 56:
        company = "MASTERCARD"
    elif number >= 40 and number <= 49:
        company = "VISA"
    else:
        company = "INVALID"

    return company


if __name__ == "__main__":
    main()