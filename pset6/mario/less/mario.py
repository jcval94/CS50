from cs50 import get_int


while True:
    # get height as integer
    ha = get_int("Height: ")
    if (ha > 0 and ha < 9):
        break


def mario(h):
    # print function
    print((" " * (h - 1)) + "#" * (ha - h + 1))

    if (h != 1):
        mario(h - 1)


mario(ha)
