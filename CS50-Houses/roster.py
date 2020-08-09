# TODO
from cs50 import SQL
import csv
import sys
import sqlite3
db = SQL("sqlite:///students.db")

#check command-line arguments
if len(sys.argv) != 2:
    sys.exit("Try Again!")

#query database for all students in house
house = sys.argv[1]
result = db.execute("SELECT * from students WHERE house = ? ORDER BY last, first", [house])
for row in result:
    #Harry James Potter, born 1980
    first_name = row["first"]
    middle_name = row["middle"]
    last_name = row["last"]
    year = row["birth"]
    if middle_name == None:
        print(f"{first_name} {last_name}, born {year}")
    else:
        print(f"{first_name} {middle_name} {last_name}, born {year}")
