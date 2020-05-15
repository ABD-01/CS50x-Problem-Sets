from sys import argv, exit
import csv


# Check for file name in Line Arguments
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)


# Opening DNA database and storing as a Tuple
with open(argv[1], "r") as database:
    data = csv.reader(database)
    data = tuple(data)

# Opening the Sample DNA and storing as a String
with open(argv[2], "r") as sample:
    dna = sample.read()


# Making a Dictionary with Name and DNA STR list.
dicdata = {}
for i in range(1, len(data)):
    dicdata[data[i][0]] = list(data[i])[1:]


# Finding the Longest sequence of a particular STR and storing in list named count[]
types_str = len(data[0]) - 1
count = [0 for n in range(types_str)]
for i in range(types_str):
    j = 0
    counter = 0
    while j < (len(dna)-len(data[0][i+1])):
        if data[0][i+1] == dna[j:j+len(data[0][i+1])]:
            counter += 1
            j += len(data[0][i+1])
            if counter > count[i]:
                count[i] = counter
        else:
            counter = 0
            j += 1


# Converting the integers in list count to strings
for rn in range(len(count)):
    count[rn] = str(count[rn])


# Finding the DNA match
found = 0
for names in dicdata:
    if dicdata[names] == count:
        print(names)
        found = 1
        break
if found != 1:
    print("No match")
