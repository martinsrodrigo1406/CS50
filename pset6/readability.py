text = input("Text: ")

wordCounter = 1
charCounter = 0
sentenceCounter = 0

for char in text:
    if ord(char) >= 65 and ord(char) <= 90:
        charCounter += 1
    if ord(char) >= 97 and ord(char) <= 122:
        charCounter += 1


for element in text:
    if element == " ":
        wordCounter += 1
    if element == "!" or element == "." or element == "?":
        sentenceCounter += 1



L = (charCounter / wordCounter) * 100

S = (sentenceCounter / wordCounter) * 100


grade = round((0.0588 * L) - (0.296 * S) - 15.8)

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print("Grade " + str(grade))

