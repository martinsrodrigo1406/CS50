

#while True:
#    owned = float(input("Change owed: "))
#    if(owned > 0):
#        break
    
i = True
while i:
    i = False
    try:
        owed = float(input("Change owed: "))
        float(owed)
    except ValueError as e:
        i = True
    if i == False and owed <= 0:
        i = True 

coins = 0
rest = 0
owed = owed * 1000

while owed >= 1:
    while owed >= 250:
        owed -= 250
        coins += 1

    while owed >= 100:
        owed -= 100
        coins += 1

    while owed >= 50:
        owed -= 50
        coins += 1

    while owed >= 10:
        owed -= 10
        coins += 1

print(coins)