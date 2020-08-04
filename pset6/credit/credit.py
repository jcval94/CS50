from cs50 import get_int


while True:
    # get height as integer
    credit_n = get_int("Number: ")
    if (credit_n > 0):
        break
n_as_strt = str(credit_n)

len_dig = len(n_as_strt)

first_two_dig = int(n_as_strt[0] + n_as_strt[1])

first_dig = int(str(credit_n)[0])

if ((first_two_dig == 34 or first_two_dig == 37) and len_dig == 15):
    print("AMEX")
elif ((first_two_dig == 51 or first_two_dig == 55) and len_dig == 16):
    print("MASTERCARD")
elif (first_dig == 4 and (len_dig == 13 or len_dig == 16)):
    print("VISA")
else:
    print("INVALID")

