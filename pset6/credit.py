j = True
while j:
    j = False
    try:
        number = int(input("Number: "))
        int(number)
    except ValueError as e:
        j = True


testLenght = number
i = 0

while testLenght >= 1:
    testLenght /= 10
    i += 1

if i == 16:
    testCard = number
    while testCard > 100:
        testCard = int(testCard / 10)

    if testCard >= 51 and testCard <= 55:
        card = "MASTERCARD"
    else:
        testCard = int(testCard / 10)
        if testCard == 4:
            card = "VISA"
        else:
            card = "INVALID"


elif i == 13:
    testCard = number
    while testCard > 10:
        testCard = int(testCard / 10)
    if testCard == 4:
        card = "VISA"
    else:
        card = "INVALID"

elif i == 15:
    testCard = number
    while testCard > 100:
        testCard = int(testCard / 10)
    if testCard == 37 or testCard == 34:
        card = "AMEX"
    else:
        card = "INVALID"

else:
    card = "INVALID"

result1 = 0
result2 = 0
temp = number

while temp >= 1:
    result1 += int(temp % 10)
    temp = int(temp / 100)

temp = number
temp = int(temp / 10)

while temp >= 1:

    if ((temp % 10) * 2) > 9:
        result2 += 1
        result2 += (int(temp % 10) * 2) - 10
    else:
        result2 += int(temp % 10) * 2
    temp = int(temp / 100)

finalResult = int(result1 + result2)
if (finalResult % 10) == 0:
    print(card)
else:
    print("INVALID")







