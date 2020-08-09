from cs50 import SQL
import csv
import sys
db = SQL("sqlite:///students.db")

if len(sys.argv) != 2:
    sys.exit("Try Again!")

with open(sys.argv[1], newline='') as f:
    reader = csv.reader(f)
    first_line = next(reader)

    student_id = 0
    for row in reader:
        name_string, house, birth = row
        birth = int(birth)
        name_list = name_string.split()
        student_id += 1

        first_name = name_list[0]
        if len(name_list) == 3:
            middle_name = name_list[1]
            last_name = name_list[2]
        if len(name_list) == 2:
            middle_name = None
            last_name = name_list[1]

        print(first_name, middle_name, last_name)
        db.execute("INSERT INTO students VALUES (?, ?, ?, ?, ?, ?);", [student_id, first_name, middle_name, last_name, house, birth])
