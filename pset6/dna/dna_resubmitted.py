from sys import argv, exit
import csv


# Check for file name in Line Arguments
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)


# Opening DNA database and storing as a Dictionary
dicdata = {}
with open(argv[1], "r") as database:
    data = csv.reader(database)
    for row in data:
        dicdata[row[0]] = (row[1:])


# Opening the Sample DNA and storing as a String
with open(argv[2], "r") as sample:
    dna = sample.read()


# Finding the Longest sequence of a particular STR and storing in list named count[]
types_str = len(dicdata["name"])
count = [0 for n in range(types_str)]
for i in range(types_str):
    j = 0
    counter = 0
    while j < (len(dna)-len(dicdata["name"][i])):
        if dicdata["name"][i] == dna[j:j+len(dicdata["name"][i])]:
            counter += 1
            j += len(dicdata["name"][i])
            if counter > int(count[i]):
                count[i] = str((counter))
        else:
            counter = 0
            j += 1


# Finding the DNA match
found = 0
for key in dicdata:
    if dicdata[key] == count:
        print(key)
        found = 1
        break
if found != 1:
    print("No match")
