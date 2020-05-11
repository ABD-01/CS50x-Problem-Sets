import cs50
import csv
from sys import argv, exit

# Creating a Databse
open("students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")

# Create table
db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

# Check for file name in Line Arguments
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# Opening CSV file
with open(argv[1], "r") as hogward:

    # Creating a Dictionary
    reader = csv.DictReader(hogward)

    # Iterating over the dictionary
    for row in reader:

        # Making a List of names
        row["name"] = row["name"].split()

        # If 2nd names doesn't exist Changing it to None
        if len(row["name"]) != 3:
            row["name"].insert(1, None)

        # Inserting into the table
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                   row["name"][0], row["name"][1], row["name"][2], row["house"], int(row["birth"]))
