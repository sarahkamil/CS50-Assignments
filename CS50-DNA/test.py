import csv
import sys

#make sure program takes exactly 3 command-line arguments
#first command-line argument: csv file containing STR counts for a list of individuals
#second command-line argument: text file containing DNA sequence to identify

if len(sys.argv) != 3:
    sys.exit("Try Again!")

#open text file containing DNA sequence to identify
with open(sys.argv[2], newline='') as f:
    sequence = f.read().strip("\n")

#open csv file containing STR counts for a list of individuals
with open(sys.argv[1], newline='') as f:
    reader = csv.reader(f)
    STR_list = next(reader)
    del STR_list[0]


#search given DNA sequence for longest run of consecutive repeats of the STR in DNA sequence
dna_signature = []
for STR in STR_list:
    highest = 1
    while STR*highest in sequence:
        highest += 1
    highest -= 1
    dna_signature.append(str(highest))


#check if DNA sequence matches DNA sequence of any of the individuals in the text file
with open(sys.argv[1], newline='') as f:
    match = False
    reader = csv.reader(f)
    next(reader)
    for line in reader:
        name = line[0]
        if dna_signature == line[1:]:
            print(name)
            match = True
    if match == False:
        print("No match")


