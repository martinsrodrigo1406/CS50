

def printBlock(h):
    if h > 1:
        printBlock(h - 1)

    print("#" * h)




def main():
    i = True
    while i:
        i = False
        try:
            height = input("Height: ")
            int(height)
        except ValueError as e:
            i = True

        if i == False:
            height = int(height)
            if height > 0 and height <= 8:
                break
            else:
                i = True

    printBlock(height)

main()
