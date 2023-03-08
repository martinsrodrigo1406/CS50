import sys
import csv


if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py data.csv sequence.txt")

with open(sys.argv[2], 'r') as dnaSeq:
    readerDna = dnaSeq.read()

i = 0
counter = 0
thisDict = {'name': ""}

biggerSeq = 0

with open(sys.argv[1], 'r') as dnaBase:
    readerBase = csv.DictReader(dnaBase)
    for strSeq in readerBase.fieldnames:
        biggerSeq = 0
        if strSeq != "name":
            i = 0
            counter = 0
            j = len(strSeq)
            while i <= (len(readerDna) - j):
                if strSeq == readerDna[i:(i + j)]:
                    counter += 1
                    i = i + j
                    if counter > biggerSeq:
                        biggerSeq = counter
                else:
                    counter = 0
                    i += 1
            thisDict[strSeq] = str(biggerSeq)



    for strCount in readerBase:
        thisDict["name"] = strCount["name"]
        if strCount == thisDict:
            print(strCount["name"])
            exit()





print("No match")























