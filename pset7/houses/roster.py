import cs50
import csv
from sys import argv, exit

db = cs50.SQL("sqlite:///students.db")

# Check for file name in Line Arguments
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

houses = ("Gryffindor", "Hufflepuff", "Ravenclaw", "Slytherin")
if argv[1] not in houses:
    print("ERROR")
    exit(1)

student = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first;", argv[1])
for row in student:
    print(row["first"], end=" ")
    if row["middle"] != None:
        print(row["middle"], end=" ")
    print(row["last"], end=", born ")
    print(row["birth"])
